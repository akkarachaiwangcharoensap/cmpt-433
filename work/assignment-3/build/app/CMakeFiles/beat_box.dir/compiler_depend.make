# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

app/CMakeFiles/beat_box.dir/src/audio_mixer.c.o: /home/aki/cmpt-433/work/assignment-3/app/src/audio_mixer.c \
  /usr/include/stdc-predef.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/audio_mixer.h \
  /home/aki/cmpt-433/work/assignment-3/hal/include/hal/periodTimer.h \
  /usr/include/alsa/asoundlib.h \
  /usr/include/unistd.h \
  /usr/include/features.h \
  /usr/include/features-time64.h \
  /usr/include/aarch64-linux-gnu/bits/wordsize.h \
  /usr/include/aarch64-linux-gnu/bits/timesize.h \
  /usr/include/aarch64-linux-gnu/sys/cdefs.h \
  /usr/include/aarch64-linux-gnu/bits/long-double.h \
  /usr/include/aarch64-linux-gnu/gnu/stubs.h \
  /usr/include/aarch64-linux-gnu/gnu/stubs-lp64.h \
  /usr/include/aarch64-linux-gnu/bits/posix_opt.h \
  /usr/include/aarch64-linux-gnu/bits/environments.h \
  /usr/include/aarch64-linux-gnu/bits/types.h \
  /usr/include/aarch64-linux-gnu/bits/typesizes.h \
  /usr/include/aarch64-linux-gnu/bits/time64.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stddef.h \
  /usr/include/aarch64-linux-gnu/bits/confname.h \
  /usr/include/aarch64-linux-gnu/bits/getopt_posix.h \
  /usr/include/aarch64-linux-gnu/bits/getopt_core.h \
  /usr/include/aarch64-linux-gnu/bits/unistd_ext.h \
  /usr/include/stdio.h \
  /usr/include/aarch64-linux-gnu/bits/libc-header-start.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stdarg.h \
  /usr/include/aarch64-linux-gnu/bits/types/__fpos_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__mbstate_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__fpos64_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__FILE.h \
  /usr/include/aarch64-linux-gnu/bits/types/FILE.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_FILE.h \
  /usr/include/aarch64-linux-gnu/bits/stdio_lim.h \
  /usr/include/aarch64-linux-gnu/bits/floatn.h \
  /usr/include/aarch64-linux-gnu/bits/floatn-common.h \
  /usr/include/stdlib.h \
  /usr/include/aarch64-linux-gnu/bits/waitflags.h \
  /usr/include/aarch64-linux-gnu/bits/waitstatus.h \
  /usr/include/aarch64-linux-gnu/sys/types.h \
  /usr/include/aarch64-linux-gnu/bits/types/clock_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/clockid_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/time_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/timer_t.h \
  /usr/include/aarch64-linux-gnu/bits/stdint-intn.h \
  /usr/include/endian.h \
  /usr/include/aarch64-linux-gnu/bits/endian.h \
  /usr/include/aarch64-linux-gnu/bits/endianness.h \
  /usr/include/aarch64-linux-gnu/bits/byteswap.h \
  /usr/include/aarch64-linux-gnu/bits/uintn-identity.h \
  /usr/include/aarch64-linux-gnu/sys/select.h \
  /usr/include/aarch64-linux-gnu/bits/select.h \
  /usr/include/aarch64-linux-gnu/bits/types/sigset_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__sigset_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_timeval.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_timespec.h \
  /usr/include/aarch64-linux-gnu/bits/pthreadtypes.h \
  /usr/include/aarch64-linux-gnu/bits/thread-shared-types.h \
  /usr/include/aarch64-linux-gnu/bits/pthreadtypes-arch.h \
  /usr/include/aarch64-linux-gnu/bits/atomic_wide_counter.h \
  /usr/include/aarch64-linux-gnu/bits/struct_mutex.h \
  /usr/include/aarch64-linux-gnu/bits/struct_rwlock.h \
  /usr/include/alloca.h \
  /usr/include/aarch64-linux-gnu/bits/stdlib-float.h \
  /usr/include/string.h \
  /usr/include/aarch64-linux-gnu/bits/types/locale_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__locale_t.h \
  /usr/include/strings.h \
  /usr/include/fcntl.h \
  /usr/include/aarch64-linux-gnu/bits/fcntl.h \
  /usr/include/aarch64-linux-gnu/bits/fcntl-linux.h \
  /usr/include/aarch64-linux-gnu/bits/stat.h \
  /usr/include/aarch64-linux-gnu/bits/struct_stat.h \
  /usr/include/assert.h \
  /usr/include/poll.h \
  /usr/include/aarch64-linux-gnu/sys/poll.h \
  /usr/include/aarch64-linux-gnu/bits/poll.h \
  /usr/include/errno.h \
  /usr/include/aarch64-linux-gnu/bits/errno.h \
  /usr/include/linux/errno.h \
  /usr/include/aarch64-linux-gnu/asm/errno.h \
  /usr/include/asm-generic/errno.h \
  /usr/include/asm-generic/errno-base.h \
  /usr/include/alsa/asoundef.h \
  /usr/include/alsa/version.h \
  /usr/include/alsa/global.h \
  /usr/include/time.h \
  /usr/include/aarch64-linux-gnu/bits/time.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_tm.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_itimerspec.h \
  /usr/include/alsa/input.h \
  /usr/include/alsa/output.h \
  /usr/include/alsa/error.h \
  /usr/include/alsa/conf.h \
  /usr/include/alsa/pcm.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stdint.h \
  /usr/include/stdint.h \
  /usr/include/aarch64-linux-gnu/bits/wchar.h \
  /usr/include/aarch64-linux-gnu/bits/stdint-uintn.h \
  /usr/include/alsa/rawmidi.h \
  /usr/include/alsa/timer.h \
  /usr/include/alsa/hwdep.h \
  /usr/include/alsa/control.h \
  /usr/include/alsa/mixer.h \
  /usr/include/alsa/seq_event.h \
  /usr/include/alsa/seq.h \
  /usr/include/alsa/seqmid.h \
  /usr/include/alsa/seq_midi_event.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stdbool.h \
  /usr/include/pthread.h \
  /usr/include/sched.h \
  /usr/include/aarch64-linux-gnu/bits/sched.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_sched_param.h \
  /usr/include/aarch64-linux-gnu/bits/cpu-set.h \
  /usr/include/aarch64-linux-gnu/bits/setjmp.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct___jmp_buf_tag.h \
  /usr/include/aarch64-linux-gnu/bits/pthread_stack_min-dynamic.h \
  /usr/include/aarch64-linux-gnu/bits/pthread_stack_min.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/limits.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/syslimits.h \
  /usr/include/limits.h \
  /usr/include/aarch64-linux-gnu/bits/posix1_lim.h \
  /usr/include/aarch64-linux-gnu/bits/local_lim.h \
  /usr/include/linux/limits.h \
  /usr/include/aarch64-linux-gnu/bits/posix2_lim.h

app/CMakeFiles/beat_box.dir/src/beat_box.c.o: /home/aki/cmpt-433/work/assignment-3/app/src/beat_box.c \
  /usr/include/stdc-predef.h \
  /usr/include/stdio.h \
  /usr/include/aarch64-linux-gnu/bits/libc-header-start.h \
  /usr/include/features.h \
  /usr/include/features-time64.h \
  /usr/include/aarch64-linux-gnu/bits/wordsize.h \
  /usr/include/aarch64-linux-gnu/bits/timesize.h \
  /usr/include/aarch64-linux-gnu/sys/cdefs.h \
  /usr/include/aarch64-linux-gnu/bits/long-double.h \
  /usr/include/aarch64-linux-gnu/gnu/stubs.h \
  /usr/include/aarch64-linux-gnu/gnu/stubs-lp64.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stddef.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stdarg.h \
  /usr/include/aarch64-linux-gnu/bits/types.h \
  /usr/include/aarch64-linux-gnu/bits/typesizes.h \
  /usr/include/aarch64-linux-gnu/bits/time64.h \
  /usr/include/aarch64-linux-gnu/bits/types/__fpos_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__mbstate_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__fpos64_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__FILE.h \
  /usr/include/aarch64-linux-gnu/bits/types/FILE.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_FILE.h \
  /usr/include/aarch64-linux-gnu/bits/stdio_lim.h \
  /usr/include/aarch64-linux-gnu/bits/floatn.h \
  /usr/include/aarch64-linux-gnu/bits/floatn-common.h \
  /usr/include/stdlib.h \
  /usr/include/aarch64-linux-gnu/bits/waitflags.h \
  /usr/include/aarch64-linux-gnu/bits/waitstatus.h \
  /usr/include/aarch64-linux-gnu/sys/types.h \
  /usr/include/aarch64-linux-gnu/bits/types/clock_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/clockid_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/time_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/timer_t.h \
  /usr/include/aarch64-linux-gnu/bits/stdint-intn.h \
  /usr/include/endian.h \
  /usr/include/aarch64-linux-gnu/bits/endian.h \
  /usr/include/aarch64-linux-gnu/bits/endianness.h \
  /usr/include/aarch64-linux-gnu/bits/byteswap.h \
  /usr/include/aarch64-linux-gnu/bits/uintn-identity.h \
  /usr/include/aarch64-linux-gnu/sys/select.h \
  /usr/include/aarch64-linux-gnu/bits/select.h \
  /usr/include/aarch64-linux-gnu/bits/types/sigset_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__sigset_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_timeval.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_timespec.h \
  /usr/include/aarch64-linux-gnu/bits/pthreadtypes.h \
  /usr/include/aarch64-linux-gnu/bits/thread-shared-types.h \
  /usr/include/aarch64-linux-gnu/bits/pthreadtypes-arch.h \
  /usr/include/aarch64-linux-gnu/bits/atomic_wide_counter.h \
  /usr/include/aarch64-linux-gnu/bits/struct_mutex.h \
  /usr/include/aarch64-linux-gnu/bits/struct_rwlock.h \
  /usr/include/alloca.h \
  /usr/include/aarch64-linux-gnu/bits/stdlib-float.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stdint.h \
  /usr/include/stdint.h \
  /usr/include/aarch64-linux-gnu/bits/wchar.h \
  /usr/include/aarch64-linux-gnu/bits/stdint-uintn.h \
  /usr/include/unistd.h \
  /usr/include/aarch64-linux-gnu/bits/posix_opt.h \
  /usr/include/aarch64-linux-gnu/bits/environments.h \
  /usr/include/aarch64-linux-gnu/bits/confname.h \
  /usr/include/aarch64-linux-gnu/bits/getopt_posix.h \
  /usr/include/aarch64-linux-gnu/bits/getopt_core.h \
  /usr/include/aarch64-linux-gnu/bits/unistd_ext.h \
  /usr/include/signal.h \
  /usr/include/aarch64-linux-gnu/bits/signum-generic.h \
  /usr/include/aarch64-linux-gnu/bits/signum-arch.h \
  /usr/include/aarch64-linux-gnu/bits/types/sig_atomic_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/siginfo_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__sigval_t.h \
  /usr/include/aarch64-linux-gnu/bits/siginfo-arch.h \
  /usr/include/aarch64-linux-gnu/bits/siginfo-consts.h \
  /usr/include/aarch64-linux-gnu/bits/types/sigval_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/sigevent_t.h \
  /usr/include/aarch64-linux-gnu/bits/sigevent-consts.h \
  /usr/include/aarch64-linux-gnu/bits/sigaction.h \
  /usr/include/aarch64-linux-gnu/bits/sigcontext.h \
  /usr/include/aarch64-linux-gnu/asm/sigcontext.h \
  /usr/include/linux/types.h \
  /usr/include/aarch64-linux-gnu/asm/types.h \
  /usr/include/asm-generic/types.h \
  /usr/include/asm-generic/int-ll64.h \
  /usr/include/aarch64-linux-gnu/asm/bitsperlong.h \
  /usr/include/asm-generic/bitsperlong.h \
  /usr/include/linux/posix_types.h \
  /usr/include/linux/stddef.h \
  /usr/include/aarch64-linux-gnu/asm/posix_types.h \
  /usr/include/asm-generic/posix_types.h \
  /usr/include/aarch64-linux-gnu/asm/sve_context.h \
  /usr/include/aarch64-linux-gnu/bits/types/stack_t.h \
  /usr/include/aarch64-linux-gnu/sys/ucontext.h \
  /usr/include/aarch64-linux-gnu/sys/procfs.h \
  /usr/include/aarch64-linux-gnu/sys/time.h \
  /usr/include/aarch64-linux-gnu/sys/user.h \
  /usr/include/aarch64-linux-gnu/bits/procfs.h \
  /usr/include/aarch64-linux-gnu/bits/procfs-id.h \
  /usr/include/aarch64-linux-gnu/bits/procfs-prregset.h \
  /usr/include/aarch64-linux-gnu/bits/procfs-extra.h \
  /usr/include/aarch64-linux-gnu/bits/sigstack.h \
  /usr/include/aarch64-linux-gnu/bits/sigstksz.h \
  /usr/include/aarch64-linux-gnu/bits/ss_flags.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_sigstack.h \
  /usr/include/aarch64-linux-gnu/bits/sigthread.h \
  /usr/include/aarch64-linux-gnu/bits/signal_ext.h \
  /usr/include/pthread.h \
  /usr/include/sched.h \
  /usr/include/aarch64-linux-gnu/bits/sched.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_sched_param.h \
  /usr/include/aarch64-linux-gnu/bits/cpu-set.h \
  /usr/include/time.h \
  /usr/include/aarch64-linux-gnu/bits/time.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_tm.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_itimerspec.h \
  /usr/include/aarch64-linux-gnu/bits/types/locale_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__locale_t.h \
  /usr/include/aarch64-linux-gnu/bits/setjmp.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct___jmp_buf_tag.h \
  /usr/include/aarch64-linux-gnu/bits/pthread_stack_min-dynamic.h \
  /usr/include/aarch64-linux-gnu/bits/pthread_stack_min.h \
  /usr/include/assert.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stdbool.h \
  /usr/include/string.h \
  /usr/include/strings.h \
  /home/aki/cmpt-433/work/assignment-3/hal/include/hal/gpio.h \
  /usr/include/gpiod.h \
  /home/aki/cmpt-433/work/assignment-3/hal/include/hal/joystick.h \
  /home/aki/cmpt-433/work/assignment-3/hal/include/hal/rotary_statemachine.h \
  /home/aki/cmpt-433/work/assignment-3/hal/include/hal/accelerometer.h \
  /home/aki/cmpt-433/work/assignment-3/hal/include/hal/lcd.h \
  /home/aki/cmpt-433/work/assignment-3/hal/include/hal/periodTimer.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/audio_mixer.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/drum_beat.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/audio_mixer.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/lcd_screens.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/udp.h

app/CMakeFiles/beat_box.dir/src/drum_beat.c.o: /home/aki/cmpt-433/work/assignment-3/app/src/drum_beat.c \
  /usr/include/stdc-predef.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/drum_beat.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/audio_mixer.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/audio_mixer.h \
  /usr/include/pthread.h \
  /usr/include/features.h \
  /usr/include/features-time64.h \
  /usr/include/aarch64-linux-gnu/bits/wordsize.h \
  /usr/include/aarch64-linux-gnu/bits/timesize.h \
  /usr/include/aarch64-linux-gnu/sys/cdefs.h \
  /usr/include/aarch64-linux-gnu/bits/long-double.h \
  /usr/include/aarch64-linux-gnu/gnu/stubs.h \
  /usr/include/aarch64-linux-gnu/gnu/stubs-lp64.h \
  /usr/include/sched.h \
  /usr/include/aarch64-linux-gnu/bits/types.h \
  /usr/include/aarch64-linux-gnu/bits/typesizes.h \
  /usr/include/aarch64-linux-gnu/bits/time64.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stddef.h \
  /usr/include/aarch64-linux-gnu/bits/types/time_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_timespec.h \
  /usr/include/aarch64-linux-gnu/bits/endian.h \
  /usr/include/aarch64-linux-gnu/bits/endianness.h \
  /usr/include/aarch64-linux-gnu/bits/sched.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_sched_param.h \
  /usr/include/aarch64-linux-gnu/bits/cpu-set.h \
  /usr/include/time.h \
  /usr/include/aarch64-linux-gnu/bits/time.h \
  /usr/include/aarch64-linux-gnu/bits/types/clock_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_tm.h \
  /usr/include/aarch64-linux-gnu/bits/types/clockid_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/timer_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_itimerspec.h \
  /usr/include/aarch64-linux-gnu/bits/types/locale_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__locale_t.h \
  /usr/include/aarch64-linux-gnu/bits/pthreadtypes.h \
  /usr/include/aarch64-linux-gnu/bits/thread-shared-types.h \
  /usr/include/aarch64-linux-gnu/bits/pthreadtypes-arch.h \
  /usr/include/aarch64-linux-gnu/bits/atomic_wide_counter.h \
  /usr/include/aarch64-linux-gnu/bits/struct_mutex.h \
  /usr/include/aarch64-linux-gnu/bits/struct_rwlock.h \
  /usr/include/aarch64-linux-gnu/bits/setjmp.h \
  /usr/include/aarch64-linux-gnu/bits/types/__sigset_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct___jmp_buf_tag.h \
  /usr/include/aarch64-linux-gnu/bits/pthread_stack_min-dynamic.h \
  /usr/include/aarch64-linux-gnu/bits/pthread_stack_min.h \
  /usr/include/unistd.h \
  /usr/include/aarch64-linux-gnu/bits/posix_opt.h \
  /usr/include/aarch64-linux-gnu/bits/environments.h \
  /usr/include/aarch64-linux-gnu/bits/confname.h \
  /usr/include/aarch64-linux-gnu/bits/getopt_posix.h \
  /usr/include/aarch64-linux-gnu/bits/getopt_core.h \
  /usr/include/aarch64-linux-gnu/bits/unistd_ext.h \
  /usr/include/stdlib.h \
  /usr/include/aarch64-linux-gnu/bits/libc-header-start.h \
  /usr/include/aarch64-linux-gnu/bits/waitflags.h \
  /usr/include/aarch64-linux-gnu/bits/waitstatus.h \
  /usr/include/aarch64-linux-gnu/bits/floatn.h \
  /usr/include/aarch64-linux-gnu/bits/floatn-common.h \
  /usr/include/aarch64-linux-gnu/sys/types.h \
  /usr/include/aarch64-linux-gnu/bits/stdint-intn.h \
  /usr/include/endian.h \
  /usr/include/aarch64-linux-gnu/bits/byteswap.h \
  /usr/include/aarch64-linux-gnu/bits/uintn-identity.h \
  /usr/include/aarch64-linux-gnu/sys/select.h \
  /usr/include/aarch64-linux-gnu/bits/select.h \
  /usr/include/aarch64-linux-gnu/bits/types/sigset_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_timeval.h \
  /usr/include/alloca.h \
  /usr/include/aarch64-linux-gnu/bits/stdlib-float.h \
  /usr/include/stdio.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stdarg.h \
  /usr/include/aarch64-linux-gnu/bits/types/__fpos_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__mbstate_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__fpos64_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__FILE.h \
  /usr/include/aarch64-linux-gnu/bits/types/FILE.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_FILE.h \
  /usr/include/aarch64-linux-gnu/bits/stdio_lim.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stdbool.h \
  /usr/include/assert.h

app/CMakeFiles/beat_box.dir/src/lcd_screens.c.o: /home/aki/cmpt-433/work/assignment-3/app/src/lcd_screens.c \
  /usr/include/stdc-predef.h \
  /home/aki/cmpt-433/work/assignment-3/lcd/lib/LCD/LCD_1in54.h \
  /home/aki/cmpt-433/work/assignment-3/lcd/lib/Config/DEV_Config.h \
  /home/aki/cmpt-433/work/assignment-3/lcd/lib/Config/Debug.h \
  /usr/include/stdio.h \
  /usr/include/aarch64-linux-gnu/bits/libc-header-start.h \
  /usr/include/features.h \
  /usr/include/features-time64.h \
  /usr/include/aarch64-linux-gnu/bits/wordsize.h \
  /usr/include/aarch64-linux-gnu/bits/timesize.h \
  /usr/include/aarch64-linux-gnu/sys/cdefs.h \
  /usr/include/aarch64-linux-gnu/bits/long-double.h \
  /usr/include/aarch64-linux-gnu/gnu/stubs.h \
  /usr/include/aarch64-linux-gnu/gnu/stubs-lp64.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stddef.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stdarg.h \
  /usr/include/aarch64-linux-gnu/bits/types.h \
  /usr/include/aarch64-linux-gnu/bits/typesizes.h \
  /usr/include/aarch64-linux-gnu/bits/time64.h \
  /usr/include/aarch64-linux-gnu/bits/types/__fpos_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__mbstate_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__fpos64_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__FILE.h \
  /usr/include/aarch64-linux-gnu/bits/types/FILE.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_FILE.h \
  /usr/include/aarch64-linux-gnu/bits/stdio_lim.h \
  /usr/include/aarch64-linux-gnu/bits/floatn.h \
  /usr/include/aarch64-linux-gnu/bits/floatn-common.h \
  /usr/include/unistd.h \
  /usr/include/aarch64-linux-gnu/bits/posix_opt.h \
  /usr/include/aarch64-linux-gnu/bits/environments.h \
  /usr/include/aarch64-linux-gnu/bits/confname.h \
  /usr/include/aarch64-linux-gnu/bits/getopt_posix.h \
  /usr/include/aarch64-linux-gnu/bits/getopt_core.h \
  /usr/include/aarch64-linux-gnu/bits/unistd_ext.h \
  /usr/include/errno.h \
  /usr/include/aarch64-linux-gnu/bits/errno.h \
  /usr/include/linux/errno.h \
  /usr/include/aarch64-linux-gnu/asm/errno.h \
  /usr/include/asm-generic/errno.h \
  /usr/include/asm-generic/errno-base.h \
  /usr/include/string.h \
  /usr/include/aarch64-linux-gnu/bits/types/locale_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__locale_t.h \
  /usr/include/strings.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stdint.h \
  /usr/include/stdint.h \
  /usr/include/aarch64-linux-gnu/bits/wchar.h \
  /usr/include/aarch64-linux-gnu/bits/stdint-intn.h \
  /usr/include/aarch64-linux-gnu/bits/stdint-uintn.h \
  /usr/include/stdlib.h \
  /usr/include/aarch64-linux-gnu/bits/waitflags.h \
  /usr/include/aarch64-linux-gnu/bits/waitstatus.h \
  /usr/include/aarch64-linux-gnu/sys/types.h \
  /usr/include/aarch64-linux-gnu/bits/types/clock_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/clockid_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/time_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/timer_t.h \
  /usr/include/endian.h \
  /usr/include/aarch64-linux-gnu/bits/endian.h \
  /usr/include/aarch64-linux-gnu/bits/endianness.h \
  /usr/include/aarch64-linux-gnu/bits/byteswap.h \
  /usr/include/aarch64-linux-gnu/bits/uintn-identity.h \
  /usr/include/aarch64-linux-gnu/sys/select.h \
  /usr/include/aarch64-linux-gnu/bits/select.h \
  /usr/include/aarch64-linux-gnu/bits/types/sigset_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__sigset_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_timeval.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_timespec.h \
  /usr/include/aarch64-linux-gnu/bits/pthreadtypes.h \
  /usr/include/aarch64-linux-gnu/bits/thread-shared-types.h \
  /usr/include/aarch64-linux-gnu/bits/pthreadtypes-arch.h \
  /usr/include/aarch64-linux-gnu/bits/atomic_wide_counter.h \
  /usr/include/aarch64-linux-gnu/bits/struct_mutex.h \
  /usr/include/aarch64-linux-gnu/bits/struct_rwlock.h \
  /usr/include/alloca.h \
  /usr/include/aarch64-linux-gnu/bits/stdlib-float.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/lcd_screens.h \
  /home/aki/cmpt-433/work/assignment-3/hal/include/hal/lcd.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/drum_beat.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/audio_mixer.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/audio_mixer.h \
  /home/aki/cmpt-433/work/assignment-3/lcd/lib/GUI/GUI_Paint.h \
  /home/aki/cmpt-433/work/assignment-3/lcd/lib/Config/Debug.h \
  /home/aki/cmpt-433/work/assignment-3/lcd/lib/Fonts/fonts.h \
  /home/aki/cmpt-433/work/assignment-3/hal/include/hal/periodTimer.h

app/CMakeFiles/beat_box.dir/src/udp.c.o: /home/aki/cmpt-433/work/assignment-3/app/src/udp.c \
  /usr/include/stdc-predef.h \
  /usr/include/stdio.h \
  /usr/include/aarch64-linux-gnu/bits/libc-header-start.h \
  /usr/include/features.h \
  /usr/include/features-time64.h \
  /usr/include/aarch64-linux-gnu/bits/wordsize.h \
  /usr/include/aarch64-linux-gnu/bits/timesize.h \
  /usr/include/aarch64-linux-gnu/sys/cdefs.h \
  /usr/include/aarch64-linux-gnu/bits/long-double.h \
  /usr/include/aarch64-linux-gnu/gnu/stubs.h \
  /usr/include/aarch64-linux-gnu/gnu/stubs-lp64.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stddef.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stdarg.h \
  /usr/include/aarch64-linux-gnu/bits/types.h \
  /usr/include/aarch64-linux-gnu/bits/typesizes.h \
  /usr/include/aarch64-linux-gnu/bits/time64.h \
  /usr/include/aarch64-linux-gnu/bits/types/__fpos_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__mbstate_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__fpos64_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__FILE.h \
  /usr/include/aarch64-linux-gnu/bits/types/FILE.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_FILE.h \
  /usr/include/aarch64-linux-gnu/bits/stdio_lim.h \
  /usr/include/aarch64-linux-gnu/bits/floatn.h \
  /usr/include/aarch64-linux-gnu/bits/floatn-common.h \
  /usr/include/stdlib.h \
  /usr/include/aarch64-linux-gnu/bits/waitflags.h \
  /usr/include/aarch64-linux-gnu/bits/waitstatus.h \
  /usr/include/aarch64-linux-gnu/sys/types.h \
  /usr/include/aarch64-linux-gnu/bits/types/clock_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/clockid_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/time_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/timer_t.h \
  /usr/include/aarch64-linux-gnu/bits/stdint-intn.h \
  /usr/include/endian.h \
  /usr/include/aarch64-linux-gnu/bits/endian.h \
  /usr/include/aarch64-linux-gnu/bits/endianness.h \
  /usr/include/aarch64-linux-gnu/bits/byteswap.h \
  /usr/include/aarch64-linux-gnu/bits/uintn-identity.h \
  /usr/include/aarch64-linux-gnu/sys/select.h \
  /usr/include/aarch64-linux-gnu/bits/select.h \
  /usr/include/aarch64-linux-gnu/bits/types/sigset_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__sigset_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_timeval.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_timespec.h \
  /usr/include/aarch64-linux-gnu/bits/pthreadtypes.h \
  /usr/include/aarch64-linux-gnu/bits/thread-shared-types.h \
  /usr/include/aarch64-linux-gnu/bits/pthreadtypes-arch.h \
  /usr/include/aarch64-linux-gnu/bits/atomic_wide_counter.h \
  /usr/include/aarch64-linux-gnu/bits/struct_mutex.h \
  /usr/include/aarch64-linux-gnu/bits/struct_rwlock.h \
  /usr/include/alloca.h \
  /usr/include/aarch64-linux-gnu/bits/stdlib-float.h \
  /usr/include/string.h \
  /usr/include/aarch64-linux-gnu/bits/types/locale_t.h \
  /usr/include/aarch64-linux-gnu/bits/types/__locale_t.h \
  /usr/include/strings.h \
  /usr/include/unistd.h \
  /usr/include/aarch64-linux-gnu/bits/posix_opt.h \
  /usr/include/aarch64-linux-gnu/bits/environments.h \
  /usr/include/aarch64-linux-gnu/bits/confname.h \
  /usr/include/aarch64-linux-gnu/bits/getopt_posix.h \
  /usr/include/aarch64-linux-gnu/bits/getopt_core.h \
  /usr/include/aarch64-linux-gnu/bits/unistd_ext.h \
  /usr/include/errno.h \
  /usr/include/aarch64-linux-gnu/bits/errno.h \
  /usr/include/linux/errno.h \
  /usr/include/aarch64-linux-gnu/asm/errno.h \
  /usr/include/asm-generic/errno.h \
  /usr/include/asm-generic/errno-base.h \
  /usr/include/pthread.h \
  /usr/include/sched.h \
  /usr/include/aarch64-linux-gnu/bits/sched.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_sched_param.h \
  /usr/include/aarch64-linux-gnu/bits/cpu-set.h \
  /usr/include/time.h \
  /usr/include/aarch64-linux-gnu/bits/time.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_tm.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_itimerspec.h \
  /usr/include/aarch64-linux-gnu/bits/setjmp.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct___jmp_buf_tag.h \
  /usr/include/aarch64-linux-gnu/bits/pthread_stack_min-dynamic.h \
  /usr/include/aarch64-linux-gnu/bits/pthread_stack_min.h \
  /usr/include/aarch64-linux-gnu/sys/socket.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_iovec.h \
  /usr/include/aarch64-linux-gnu/bits/socket.h \
  /usr/include/aarch64-linux-gnu/bits/socket_type.h \
  /usr/include/aarch64-linux-gnu/bits/sockaddr.h \
  /usr/include/aarch64-linux-gnu/asm/socket.h \
  /usr/include/asm-generic/socket.h \
  /usr/include/linux/posix_types.h \
  /usr/include/linux/stddef.h \
  /usr/include/aarch64-linux-gnu/asm/posix_types.h \
  /usr/include/asm-generic/posix_types.h \
  /usr/include/aarch64-linux-gnu/asm/bitsperlong.h \
  /usr/include/asm-generic/bitsperlong.h \
  /usr/include/aarch64-linux-gnu/asm/sockios.h \
  /usr/include/asm-generic/sockios.h \
  /usr/include/aarch64-linux-gnu/bits/types/struct_osockaddr.h \
  /usr/include/netinet/in.h \
  /usr/include/aarch64-linux-gnu/bits/stdint-uintn.h \
  /usr/include/aarch64-linux-gnu/bits/in.h \
  /usr/include/arpa/inet.h \
  /usr/lib/gcc/aarch64-linux-gnu/12/include/stdbool.h \
  /usr/include/assert.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/drum_beat.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/audio_mixer.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/audio_mixer.h \
  /home/aki/cmpt-433/work/assignment-3/app/include/udp.h


/usr/include/aarch64-linux-gnu/bits/in.h:

/usr/include/aarch64-linux-gnu/asm/sockios.h:

/usr/include/aarch64-linux-gnu/bits/sockaddr.h:

/usr/include/aarch64-linux-gnu/bits/types/struct_iovec.h:

/home/aki/cmpt-433/work/assignment-3/app/src/udp.c:

/home/aki/cmpt-433/work/assignment-3/lcd/lib/Fonts/fonts.h:

/home/aki/cmpt-433/work/assignment-3/lcd/lib/GUI/GUI_Paint.h:

/home/aki/cmpt-433/work/assignment-3/lcd/lib/Config/Debug.h:

/home/aki/cmpt-433/work/assignment-3/lcd/lib/Config/DEV_Config.h:

/home/aki/cmpt-433/work/assignment-3/app/include/lcd_screens.h:

/home/aki/cmpt-433/work/assignment-3/hal/include/hal/lcd.h:

/home/aki/cmpt-433/work/assignment-3/hal/include/hal/rotary_statemachine.h:

/home/aki/cmpt-433/work/assignment-3/app/src/drum_beat.c:

/home/aki/cmpt-433/work/assignment-3/hal/include/hal/joystick.h:

/home/aki/cmpt-433/work/assignment-3/hal/include/hal/gpio.h:

/usr/include/aarch64-linux-gnu/bits/sigthread.h:

/usr/include/aarch64-linux-gnu/bits/ss_flags.h:

/usr/include/aarch64-linux-gnu/bits/sigstack.h:

/usr/include/aarch64-linux-gnu/bits/procfs-prregset.h:

/usr/include/aarch64-linux-gnu/bits/procfs-id.h:

/usr/include/aarch64-linux-gnu/sys/procfs.h:

/usr/include/aarch64-linux-gnu/sys/ucontext.h:

/usr/include/aarch64-linux-gnu/bits/types/stack_t.h:

/usr/include/aarch64-linux-gnu/asm/sve_context.h:

/usr/include/aarch64-linux-gnu/asm/posix_types.h:

/usr/include/linux/stddef.h:

/usr/include/linux/posix_types.h:

/usr/include/asm-generic/bitsperlong.h:

/usr/include/aarch64-linux-gnu/asm/bitsperlong.h:

/usr/include/aarch64-linux-gnu/asm/types.h:

/usr/include/linux/types.h:

/home/aki/cmpt-433/work/assignment-3/app/include/udp.h:

/usr/include/aarch64-linux-gnu/bits/sigcontext.h:

/usr/include/aarch64-linux-gnu/bits/sigaction.h:

/usr/include/aarch64-linux-gnu/bits/sigevent-consts.h:

/usr/include/aarch64-linux-gnu/bits/types/sigevent_t.h:

/usr/include/aarch64-linux-gnu/bits/siginfo-consts.h:

/usr/include/aarch64-linux-gnu/bits/siginfo-arch.h:

/usr/include/aarch64-linux-gnu/bits/types/__sigval_t.h:

/usr/include/aarch64-linux-gnu/bits/types/sig_atomic_t.h:

/usr/include/aarch64-linux-gnu/bits/signum-generic.h:

/usr/include/aarch64-linux-gnu/bits/pthreadtypes-arch.h:

/usr/include/aarch64-linux-gnu/bits/pthreadtypes.h:

/usr/include/aarch64-linux-gnu/bits/types/struct_timeval.h:

/usr/include/aarch64-linux-gnu/bits/uintn-identity.h:

/usr/include/aarch64-linux-gnu/sys/cdefs.h:

/usr/include/alsa/control.h:

/usr/include/aarch64-linux-gnu/bits/socket.h:

/usr/include/aarch64-linux-gnu/sys/time.h:

/usr/include/aarch64-linux-gnu/bits/endian.h:

/usr/include/gpiod.h:

/usr/include/aarch64-linux-gnu/bits/procfs-extra.h:

/usr/include/endian.h:

/usr/include/aarch64-linux-gnu/bits/types/time_t.h:

/usr/include/aarch64-linux-gnu/bits/types/clockid_t.h:

/usr/include/aarch64-linux-gnu/bits/types/sigset_t.h:

/usr/include/aarch64-linux-gnu/sys/types.h:

/usr/include/aarch64-linux-gnu/bits/waitstatus.h:

/usr/include/stdlib.h:

/usr/lib/gcc/aarch64-linux-gnu/12/include/limits.h:

/usr/include/aarch64-linux-gnu/bits/floatn-common.h:

/usr/include/aarch64-linux-gnu/bits/types/__locale_t.h:

/usr/include/aarch64-linux-gnu/bits/stdio_lim.h:

/usr/lib/gcc/aarch64-linux-gnu/12/include/stdarg.h:

/home/aki/cmpt-433/work/assignment-3/app/include/drum_beat.h:

/usr/lib/gcc/aarch64-linux-gnu/12/include/syslimits.h:

/usr/include/aarch64-linux-gnu/bits/types/__FILE.h:

/usr/include/alsa/seq_event.h:

/usr/include/aarch64-linux-gnu/bits/types/struct_FILE.h:

/usr/include/aarch64-linux-gnu/bits/posix2_lim.h:

/usr/include/aarch64-linux-gnu/asm/socket.h:

/usr/include/aarch64-linux-gnu/bits/stdint-intn.h:

/usr/include/aarch64-linux-gnu/gnu/stubs.h:

/usr/include/aarch64-linux-gnu/bits/sigstksz.h:

/usr/include/poll.h:

/usr/include/features-time64.h:

/usr/include/aarch64-linux-gnu/bits/types/__mbstate_t.h:

/usr/include/linux/errno.h:

/usr/include/aarch64-linux-gnu/bits/endianness.h:

/usr/include/aarch64-linux-gnu/bits/local_lim.h:

/home/aki/cmpt-433/work/assignment-3/app/src/beat_box.c:

/usr/include/aarch64-linux-gnu/bits/libc-header-start.h:

/usr/include/aarch64-linux-gnu/bits/long-double.h:

/usr/include/aarch64-linux-gnu/bits/typesizes.h:

/usr/include/aarch64-linux-gnu/bits/socket_type.h:

/usr/include/aarch64-linux-gnu/sys/user.h:

/usr/include/aarch64-linux-gnu/bits/types/siginfo_t.h:

/usr/lib/gcc/aarch64-linux-gnu/12/include/stdbool.h:

/usr/include/pthread.h:

/usr/include/alsa/seq.h:

/usr/include/aarch64-linux-gnu/bits/types/sigval_t.h:

/usr/include/aarch64-linux-gnu/bits/thread-shared-types.h:

/usr/include/features.h:

/usr/include/aarch64-linux-gnu/gnu/stubs-lp64.h:

/usr/include/aarch64-linux-gnu/bits/confname.h:

/usr/include/aarch64-linux-gnu/bits/types/clock_t.h:

/usr/include/aarch64-linux-gnu/bits/getopt_posix.h:

/usr/include/aarch64-linux-gnu/bits/types/struct_itimerspec.h:

/usr/include/aarch64-linux-gnu/bits/waitflags.h:

/home/aki/cmpt-433/work/assignment-3/lcd/lib/LCD/LCD_1in54.h:

/usr/include/errno.h:

/usr/include/aarch64-linux-gnu/bits/types/FILE.h:

/usr/include/aarch64-linux-gnu/bits/types/struct_osockaddr.h:

/usr/include/unistd.h:

/home/aki/cmpt-433/work/assignment-3/hal/include/hal/accelerometer.h:

/usr/include/aarch64-linux-gnu/asm/errno.h:

/usr/include/arpa/inet.h:

/usr/include/aarch64-linux-gnu/bits/select.h:

/usr/include/aarch64-linux-gnu/bits/timesize.h:

/usr/include/assert.h:

/usr/include/aarch64-linux-gnu/bits/types/locale_t.h:

/usr/include/asm-generic/posix_types.h:

/usr/include/stdc-predef.h:

/usr/include/aarch64-linux-gnu/bits/types/struct___jmp_buf_tag.h:

/home/aki/cmpt-433/work/assignment-3/app/src/audio_mixer.c:

/usr/include/aarch64-linux-gnu/bits/getopt_core.h:

/usr/include/aarch64-linux-gnu/bits/environments.h:

/usr/include/alsa/asoundlib.h:

/usr/include/aarch64-linux-gnu/bits/types/__fpos_t.h:

/home/aki/cmpt-433/work/assignment-3/app/src/lcd_screens.c:

/usr/include/aarch64-linux-gnu/bits/struct_stat.h:

/usr/include/aarch64-linux-gnu/bits/stdlib-float.h:

/usr/include/aarch64-linux-gnu/bits/time.h:

/usr/include/asm-generic/int-ll64.h:

/usr/include/aarch64-linux-gnu/bits/types/timer_t.h:

/usr/include/aarch64-linux-gnu/bits/errno.h:

/usr/include/stdio.h:

/usr/include/netinet/in.h:

/usr/include/aarch64-linux-gnu/bits/types/struct_timespec.h:

/usr/include/aarch64-linux-gnu/bits/signum-arch.h:

/usr/include/aarch64-linux-gnu/sys/select.h:

/usr/include/aarch64-linux-gnu/bits/byteswap.h:

/usr/include/aarch64-linux-gnu/bits/unistd_ext.h:

/usr/lib/gcc/aarch64-linux-gnu/12/include/stddef.h:

/usr/include/aarch64-linux-gnu/bits/signal_ext.h:

/usr/include/alsa/seqmid.h:

/usr/include/aarch64-linux-gnu/bits/atomic_wide_counter.h:

/usr/include/alsa/asoundef.h:

/usr/include/aarch64-linux-gnu/bits/setjmp.h:

/usr/include/aarch64-linux-gnu/bits/types.h:

/usr/include/aarch64-linux-gnu/bits/struct_mutex.h:

/usr/include/aarch64-linux-gnu/bits/time64.h:

/usr/include/alloca.h:

/usr/include/aarch64-linux-gnu/sys/socket.h:

/usr/include/strings.h:

/usr/include/aarch64-linux-gnu/bits/types/__fpos64_t.h:

/usr/include/aarch64-linux-gnu/bits/fcntl-linux.h:

/usr/include/aarch64-linux-gnu/bits/floatn.h:

/usr/include/aarch64-linux-gnu/bits/posix_opt.h:

/usr/include/aarch64-linux-gnu/bits/posix1_lim.h:

/usr/include/aarch64-linux-gnu/bits/fcntl.h:

/usr/include/limits.h:

/usr/include/aarch64-linux-gnu/bits/stat.h:

/usr/include/aarch64-linux-gnu/sys/poll.h:

/usr/include/sched.h:

/usr/include/aarch64-linux-gnu/bits/poll.h:

/usr/include/asm-generic/types.h:

/usr/include/aarch64-linux-gnu/bits/wordsize.h:

/usr/include/asm-generic/errno-base.h:

/home/aki/cmpt-433/work/assignment-3/app/include/audio_mixer.h:

/usr/include/aarch64-linux-gnu/bits/types/__sigset_t.h:

/usr/include/alsa/error.h:

/usr/include/alsa/version.h:

/usr/include/asm-generic/socket.h:

/usr/include/alsa/global.h:

/usr/include/string.h:

/usr/include/alsa/timer.h:

/usr/include/time.h:

/usr/include/fcntl.h:

/usr/include/aarch64-linux-gnu/bits/types/struct_tm.h:

/usr/include/alsa/input.h:

/usr/include/aarch64-linux-gnu/bits/wchar.h:

/usr/include/alsa/output.h:

/usr/include/alsa/conf.h:

/usr/include/alsa/pcm.h:

/usr/include/aarch64-linux-gnu/bits/procfs.h:

/usr/lib/gcc/aarch64-linux-gnu/12/include/stdint.h:

/usr/include/aarch64-linux-gnu/bits/types/struct_sigstack.h:

/home/aki/cmpt-433/work/assignment-3/hal/include/hal/periodTimer.h:

/usr/include/aarch64-linux-gnu/bits/stdint-uintn.h:

/usr/include/aarch64-linux-gnu/asm/sigcontext.h:

/usr/include/alsa/rawmidi.h:

/usr/include/asm-generic/errno.h:

/usr/include/alsa/hwdep.h:

/usr/include/alsa/mixer.h:

/usr/include/alsa/seq_midi_event.h:

/usr/include/aarch64-linux-gnu/bits/sched.h:

/usr/include/aarch64-linux-gnu/bits/struct_rwlock.h:

/usr/include/aarch64-linux-gnu/bits/pthread_stack_min-dynamic.h:

/usr/include/aarch64-linux-gnu/bits/types/struct_sched_param.h:

/usr/include/asm-generic/sockios.h:

/usr/include/aarch64-linux-gnu/bits/cpu-set.h:

/usr/include/aarch64-linux-gnu/bits/pthread_stack_min.h:

/usr/include/stdint.h:

/usr/include/linux/limits.h:

/usr/include/signal.h:
