# DFT Guide

This section describes the basic DFT requirements.

## Shared-bus Design

The traditional design flow of inserting MBIST around Memory has increasingly highlighted the contradiction of PPA (Performance, Power, Area) on high-performance processors. In order to avoid affecting the function timing as much as possible, reduce the area cost of MBIST, and reduce the test power consumption of MBIST, NANHU adopts the MBIST bus interface based on sharedbus.
