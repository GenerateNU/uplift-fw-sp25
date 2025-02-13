# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\amant\Generate\Uplift-Solutions\uplift-fw-sp25\src\psoc_4200_uplift.cydsn\psoc_4200_uplift.cyprj
# Date: Wed, 12 Feb 2025 03:44:04 GMT
#set_units -time ns
create_clock -name {Clock_1(FFB)} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/ff_div_8}] [get_pins {ClockBlock/ff_div_9}]]
create_clock -name {I2C_0_SCBCLK(FFB)} -period 625 -waveform {0 312.5} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {CyRouted1} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 3 5} [list]
create_generated_clock -name {I2C_0_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 15 31} [list]


# Component constraints for C:\Users\amant\Generate\Uplift-Solutions\uplift-fw-sp25\src\psoc_4200_uplift.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\amant\Generate\Uplift-Solutions\uplift-fw-sp25\src\psoc_4200_uplift.cydsn\psoc_4200_uplift.cyprj
# Date: Wed, 12 Feb 2025 03:44:03 GMT
