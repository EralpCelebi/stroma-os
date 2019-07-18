#pragma once

#include <timer.h>
#include <io.h>
#include <isr.h>
#include <stdio.h>

void timerstart(uint32_t freq, isr_t handler);