#!/bin/sh

cd /home/chunhau.tan/power_management/ventana_qemu/andrew/kvm-unit-test
./configure --arch=riscv64 --cross-prefix=riscv64-poky-linux-
make clean
unset LDFLAGS
make rpmi=on VERBOSE=1 -j4
cd /home/chunhau.tan/power_management/ventana_qemu/opensbi1
make PLATFORM=generic FW_PAYLOAD_PATH=/home/chunhau.tan/power_management/ventana_qemu/andrew/kvm-unit-test/riscv/rpmi_testsuite/platform/sbi_payload/run_test.flat -j4
cd /home/chunhau.tan/power_management/ventana_qemu
./qemu/build/qemu-system-riscv64 -M virt,rpmi=on -m 2G -nographic -smp 4 -bios ./opensbi1/build/platform/generic/firmware/fw_payload.bin
