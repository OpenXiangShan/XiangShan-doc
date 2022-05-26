
VCS Simulation Introduction
===========================================

XiangShan supports VCS simulation, and diff-test with golden modle, such as NEMU or spike. Other simulation tools like LightSSS is not supported when simulated with VCS.


# Operation

Enter root path `XiangShan`, run:

```
make simv RELEASE=1
```

`simv` file will be generated in difftest. Then, run:

```
./difftest/simv [+workload=WorkloadName.bin] [+flash=Flash.bin] [+dump-wave] [+diff=Nemu-so] [+no-diff] [+max-cycles=MaxCycleNum]
```

Description of simv's parameters:

* +workload=: By default simv uses `XiangShan/ram.bin` as input.
* +flash=: By default, simv uses built-in flash, which will jump to 0x20_0000_0000.
* +dump-wave: By default, simv will not dump waveform. Waveform file is simv.vpd.
* +diff=: By default, simv will use $NEMU_HOME/build/riscv64-nemu-interpreter-so as golden model for diff-test. This will assign a golden model manually.
* +no-diff: By default, simv will enable diff-test. This will disable diff-test.
* +max-cycles=: By default, max-cycles is 0 for no limit.

# Simulation Codes

VCS simulation codes can be divided into `compilation` and `execution`.

## Compilation

Compilation can be divided into two parts:

1. **generating verilog files, in XiangShan/build**
2. **compiling verilog files with vcs**

what does *make simv* do:
``` sh
# XiangShan/Makefile:
# 1. generating verilog codes from Chisel codes:
SIM_TOP_V = $(BUILD_DIR)/$(SIM_TOP).v
$(SIM_TOP_V): $(SCALA_FILE) $(TEST_FILE)
	# ...
	@echo "\n[mill] Generating Verilog files..." > $(TIMELOG)
	$(TIME_CMD) mill -i XiangShan.test.runMain $(SIMTOP) -td $(@D)  \
		--config $(CONFIG)                                            \
		$(SIM_MEM_ARGS)                                               \
		--num-cores $(NUM_CORES)                                      \
		$(SIM_ARGS) $(FC_ARGS)
  # ...

simv:
	$(MAKE) -C ./difftest simv SIM_TOP=SimTop DESIGN_DIR=$(NOOP_HOME) NUM_CORES=$(NUM_CORES)

# XiangShan/difftest/vcs.mk:
# 2. compiling verilog codes with vcs
VCS_TARGET = simv
$(VCS_TARGET): $(SIM_TOP_V) $(VCS_CXXFILES) $(VCS_VFILES)
	vcs $(VCS_FLAGS) $(SIM_TOP_V) $(VCS_CXXFILES) $(VCS_VFILES)

```

## Execution

Execution codes can be divided into two parts: verilog files including testbench top modules, C/C++ files including initialization and difftest functions.

The top module of testbench is `tb_top`. The top module of XiangShan is `SimTop`:
```verilog
// XiangShan/difftest/src/test/vsrc/vcs/top.v
// ...
module tb_top();
// ...
  // enable waveform
  if ($test$plusargs("dump-wave")) begin
    $vcdplusfile("simv.vpd");
    $vcdpluson;
  end
  // workload: bin file, only parse parameters here.
  if ($test$plusargs("workload")) begin
    $value$plusargs("workload=%s", bin_file);
    set_bin_file(bin_file);
  end
// ...

reg has_init;
always @(posedge clock) begin
  // init
  if (reset) begin
    has_init <= 1'b0;
  end
  else if (!has_init) begin
    simv_init();
    has_init <= 1'b1;
  end

  // check errors
  if (!reset && has_init) begin
    if (simv_step()) begin
      $finish();
    end
  end
```

C/C++ codes take the initialization job of workload, difftest and device .etc and do difftest。
```C++
// XiangShan/difftest/src/test/csrc/vcs/main.cpp
// initialization, including workload, difftest, device, multi-core golden memory, golden model(nemu or spike).
extern "C" void simv_init() {
  printf("simv compiled at %s, %s\n", __DATE__, __TIME__);
  setlocale(LC_NUMERIC, "");

  init_ram(bin_file);

  difftest_init();
  init_device();
  init_goldenmem();
  init_nemuproxy();

  assert_init();
}

// difftest check at every cycle
extern "C" int simv_step() {
  if (assert_count > 0) {
    return 1;
  }
  if (difftest_state() != -1) {
    int trapCode = difftest_state();
    switch (trapCode) {
      case 0:
        eprintf(ANSI_COLOR_GREEN "HIT GOOD TRAP\n" ANSI_COLOR_RESET);
        break;
      default:
        eprintf(ANSI_COLOR_RED "Unknown trap code: %d\n", trapCode);
    }
    return trapCode + 1;
  }
  return difftest_step();
}
```