VCS 仿真测试框架介绍
===========================================

香山支持 VCS 仿真，并与 golden model 进行 difftest。VCS 仿真目前不支持 LightSSS 等验证工具。

# 操作流程

进入香山根目录，执行，进行编译：

Enter root path `XiangShan`, run:

```sh
make simv RELEASE=1
```

`simv` 会被在 `difftest` 目录中生成。之后执行：

```
./difftest/simv [+workload=WorkloadName.bin] [+flash=Flash.bin] [+dump-wave=[vpd,fsdb]] [+diff=Nemu-so] [+no-diff] [+max-cycles=MaxCycleNum]
```

simv 参数说明如下:

* +workload=: By default simv uses `XiangShan/ram.bin` as input.
* +flash=: By default, simv uses built-in flash, which will jump to 0x20_0000_0000.
* +dump-wave=: By default, simv will not dump waveform. Can be either vpd or fsdb format.
* +diff=: By default, simv will use $NEMU_HOME/build/riscv64-nemu-interpreter-so as golden model for diff-test. This will assign a golden model manually.
* +no-diff: By default, simv will enable diff-test. This will disable diff-test.
* +max-cycles=: By default, max-cycles is 0 for no limit.

# 仿真框架解析

VCS 的仿真验证框架分为 `编译` 和 `执行` 两部分。

## 编译

编译分为两部分，

1. **生成 verilog 代码，在XiangShan/build目录**
2. **vcs 编译 verilog 代码，生成仿真程序**

*make simv* 流程对应这两步：
``` sh
# XiangShan/Makefile:
# 1. 生成 verilog 代码
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
# 2. vcs 编译 verilog 代码
VCS_TARGET = simv
$(VCS_TARGET): $(SIM_TOP_V) $(VCS_CXXFILES) $(VCS_VFILES)
	vcs $(VCS_FLAGS) $(SIM_TOP_V) $(VCS_CXXFILES) $(VCS_VFILES)

```

## 执行

执行代码分为两部分，一部分是 verilog 仿真顶层代码，另一部分是 C/C++ 代码。

verilog 顶层激励模块，进行一些初始化，以及调用 C/C++ 代码。

仿真的顶层为 `tb_top`，香山核顶层模块为 `SimTop`：
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

C/C++ 负责一些 workload，difftest 等初始化，以及进行 difftest 检查等等。
```C++
// XiangShan/difftest/src/test/csrc/vcs/main.cpp
// 初始化，包括 workload、difftest、外设、双核golden内存、nemu（golden模型）
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

// 每一周期都执行 simv_step，进行 difftest 检查
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