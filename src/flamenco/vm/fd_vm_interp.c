#include "fd_vm_base.h"
#include "fd_vm_private.h"

/* FIXME: MAKE DIFFERENT VERSIONS FOR EACH COMBO OF CHECK_ALIGN/TRACE? */
/* TODO: factor out common unpacking code */

int fd_vm_exec_notrace(fd_vm_t *vm) {

  ulong frame_max = (64UL);

  ulong const *restrict text = vm->text;
  ulong text_cnt = vm->text_cnt;
  ulong entry_pc = vm->entry_pc;
  ulong const *restrict calldests = vm->calldests;

  fd_sbpf_syscalls_t const *restrict syscalls = vm->syscalls;

  ulong const *restrict region_haddr = vm->region_haddr;
  uint const *restrict region_ld_sz = vm->region_ld_sz;
  uint const *restrict region_st_sz = vm->region_st_sz;

  ulong *restrict reg = vm->reg;

  fd_vm_shadow_t *restrict shadow = vm->shadow;

  int err = (0);

// # 1 "src/flamenco/vm/fd_vm_interp_core.c" 1
// # 12 "src/flamenco/vm/fd_vm_interp_core.c"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
  // # 24 "src/flamenco/vm/fd_vm_interp_core.c"
  // # 1 "src/flamenco/vm/fd_vm_interp_jump_table.c" 1

  static void const *interp_jump_table[(4UL)][256] = {

      {
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x04, &&interp_0x05, &&sigill,      &&interp_0x07,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x0c, &&sigill,      &&sigill,      &&interp_0x0f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x14, &&interp_0x15, &&sigill,      &&interp_0x17,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x1c, &&interp_0x1d, &&sigill,      &&interp_0x1f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x25, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x2d, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x35, &&interp_0x36, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x3d, &&interp_0x3e, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x44, &&interp_0x45, &&interp_0x46, &&interp_0x47,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x4c, &&interp_0x4d, &&interp_0x4e, &&interp_0x4f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x54, &&interp_0x55, &&interp_0x56, &&interp_0x57,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x5c, &&interp_0x5d, &&interp_0x5e, &&interp_0x5f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x64, &&interp_0x65, &&interp_0x66, &&interp_0x67,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x6c, &&interp_0x6d, &&interp_0x6e, &&interp_0x6f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x74, &&interp_0x75, &&interp_0x76, &&interp_0x77,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x7c, &&interp_0x7d, &&interp_0x7e, &&interp_0x7f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x85, &&interp_0x86, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x8c, &&interp_0x8d, &&interp_0x8e, &&interp_0x8f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x95, &&interp_0x96, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x9e, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xa4, &&interp_0xa5, &&sigill,      &&interp_0xa7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xac, &&interp_0xad, &&sigill,      &&interp_0xaf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xb4, &&interp_0xb5, &&interp_0xb6, &&interp_0xb7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xbc, &&interp_0xbd, &&interp_0xbe, &&interp_0xbf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xc4, &&interp_0xc5, &&interp_0xc6, &&interp_0xc7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xcc, &&interp_0xcd, &&interp_0xce, &&interp_0xcf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0xd5, &&interp_0xd6, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xdc, &&interp_0xdd, &&interp_0xde, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xe6, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xee, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xf6, &&interp_0xf7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xfe, &&sigill,
      },
      {

          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x04, &&interp_0x05, &&sigill,      &&interp_0x07,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x0c, &&sigill,      &&sigill,      &&interp_0x0f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x14, &&interp_0x15, &&sigill,      &&interp_0x17,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x1c, &&interp_0x1d, &&sigill,      &&interp_0x1f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x25, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x2d, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x35, &&interp_0x36, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x3d, &&interp_0x3e, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x44, &&interp_0x45, &&interp_0x46, &&interp_0x47,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x4c, &&interp_0x4d, &&interp_0x4e, &&interp_0x4f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x54, &&interp_0x55, &&interp_0x56, &&interp_0x57,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x5c, &&interp_0x5d, &&interp_0x5e, &&interp_0x5f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x64, &&interp_0x65, &&interp_0x66, &&interp_0x67,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x6c, &&interp_0x6d, &&interp_0x6e, &&interp_0x6f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x74, &&interp_0x75, &&interp_0x76, &&interp_0x77,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x7c, &&interp_0x7d, &&interp_0x7e, &&interp_0x7f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x85, &&interp_0x86, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x8c, &&interp_0x8d, &&interp_0x8e, &&interp_0x8f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x95, &&interp_0x96, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x9e, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xa4, &&interp_0xa5, &&sigill,      &&interp_0xa7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xac, &&interp_0xad, &&sigill,      &&interp_0xaf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xb4, &&interp_0xb5, &&interp_0xb6, &&interp_0xb7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xbc, &&interp_0xbd, &&interp_0xbe, &&interp_0xbf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xc4, &&interp_0xc5, &&interp_0xc6, &&interp_0xc7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xcc, &&interp_0xcd, &&interp_0xce, &&interp_0xcf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0xd5, &&interp_0xd6, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xdc, &&interp_0xdd, &&interp_0xde, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xe6, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xee, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xf6, &&interp_0xf7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xfe, &&sigill,
      },
      {

          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x04, &&interp_0x05, &&sigill,      &&interp_0x07,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x0c, &&sigill,      &&sigill,      &&interp_0x0f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x14, &&interp_0x15, &&sigill,      &&interp_0x17,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x1c, &&interp_0x1d, &&sigill,      &&interp_0x1f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x25, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x2d, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x35, &&interp_0x36, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x3d, &&interp_0x3e, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x44, &&interp_0x45, &&interp_0x46, &&interp_0x47,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x4c, &&interp_0x4d, &&interp_0x4e, &&interp_0x4f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x54, &&interp_0x55, &&interp_0x56, &&interp_0x57,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x5c, &&interp_0x5d, &&interp_0x5e, &&interp_0x5f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x64, &&interp_0x65, &&interp_0x66, &&interp_0x67,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x6c, &&interp_0x6d, &&interp_0x6e, &&interp_0x6f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x74, &&interp_0x75, &&interp_0x76, &&interp_0x77,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x7c, &&interp_0x7d, &&interp_0x7e, &&interp_0x7f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x85, &&interp_0x86, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x8c, &&interp_0x8d, &&interp_0x8e, &&interp_0x8f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x95, &&interp_0x96, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x9e, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xa4, &&interp_0xa5, &&sigill,      &&interp_0xa7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xac, &&interp_0xad, &&sigill,      &&interp_0xaf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xb4, &&interp_0xb5, &&interp_0xb6, &&interp_0xb7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xbc, &&interp_0xbd, &&interp_0xbe, &&interp_0xbf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xc4, &&interp_0xc5, &&interp_0xc6, &&interp_0xc7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xcc, &&interp_0xcd, &&interp_0xce, &&interp_0xcf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0xd5, &&interp_0xd6, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xdc, &&interp_0xdd, &&interp_0xde, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xe6, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xee, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xf6, &&interp_0xf7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xfe, &&sigill,
      },
      {

          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x04, &&interp_0x05,
          &&sigill,      &&interp_0x07, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0x0c, &&sigill,      &&sigill,
          &&interp_0x0f, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x14,
          &&interp_0x15, &&sigill,      &&interp_0x17,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x1c, &&interp_0x1d,
          &&sigill,      &&interp_0x1f, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x25, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0x2d, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x35,
          &&interp_0x36, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x3d, &&interp_0x3e,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x44,
          &&interp_0x45, &&interp_0x46, &&interp_0x47,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x4c, &&interp_0x4d,
          &&interp_0x4e, &&interp_0x4f, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0x54, &&interp_0x55, &&interp_0x56,
          &&interp_0x57, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x5c,
          &&interp_0x5d, &&interp_0x5e, &&interp_0x5f,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x64, &&interp_0x65,
          &&interp_0x66, &&interp_0x67, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0x6c, &&interp_0x6d, &&interp_0x6e,
          &&interp_0x6f, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x74,
          &&interp_0x75, &&interp_0x76, &&interp_0x77,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x7c, &&interp_0x7d,
          &&interp_0x7e, &&interp_0x7f, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x85, &&interp_0x86,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x8c,
          &&interp_0x8d, &&interp_0x8e, &&interp_0x8f,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x95,
          &&interp_0x96, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x9e,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xa4,
          &&interp_0xa5, &&sigill,      &&interp_0xa7,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0xac, &&interp_0xad,
          &&sigill,      &&interp_0xaf, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0xb4, &&interp_0xb5, &&interp_0xb6,
          &&interp_0xb7, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xbc,
          &&interp_0xbd, &&interp_0xbe, &&interp_0xbf,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0xc4, &&interp_0xc5,
          &&interp_0xc6, &&interp_0xc7, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0xcc, &&interp_0xcd, &&interp_0xce,
          &&interp_0xcf, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0xd5, &&interp_0xd6, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0xdc, &&interp_0xdd,
          &&interp_0xde, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xe6,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0xee, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0xf6, &&interp_0xf7, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xfe,
          &&sigill

      }};
  // # 25 "src/flamenco/vm/fd_vm_interp_core.c" 2

  ulong sbpf_version = vm->sbpf_version;

  for (ulong table_sbpf_version = 0UL; table_sbpf_version < (4UL);
       table_sbpf_version++) {

    interp_jump_table[table_sbpf_version][0x18] =
        (table_sbpf_version < (2UL)) ? &&interp_0x18 : &&sigill;
    interp_jump_table[table_sbpf_version][0xf7] =
        (table_sbpf_version < (2UL)) ? &&sigill : &&interp_0xf7;

    interp_jump_table[table_sbpf_version][0xd4] =
        (table_sbpf_version < (2UL)) ? &&interp_0xd4 : &&sigill;

    interp_jump_table[table_sbpf_version][0x61] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x8c;
    interp_jump_table[table_sbpf_version][0x62] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x87;
    interp_jump_table[table_sbpf_version][0x63] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x8f;
    interp_jump_table[table_sbpf_version][0x8c] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x8c : &&sigill;
    interp_jump_table[table_sbpf_version][0x87] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x87 : &&interp_0x87depr;
    interp_jump_table[table_sbpf_version][0x8f] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x8f : &&sigill;

    interp_jump_table[table_sbpf_version][0x69] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x3c;
    interp_jump_table[table_sbpf_version][0x6a] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x37;
    interp_jump_table[table_sbpf_version][0x6b] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x3f;
    interp_jump_table[table_sbpf_version][0x3c] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x3c : &&interp_0x3cdepr;
    interp_jump_table[table_sbpf_version][0x37] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x37 : &&interp_0x37depr;
    interp_jump_table[table_sbpf_version][0x3f] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x3f : &&interp_0x3fdepr;

    interp_jump_table[table_sbpf_version][0x71] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x2c;
    interp_jump_table[table_sbpf_version][0x72] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x27;
    interp_jump_table[table_sbpf_version][0x73] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x2f;
    interp_jump_table[table_sbpf_version][0x2c] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x2c : &&interp_0x2cdepr;
    interp_jump_table[table_sbpf_version][0x27] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x27 : &&interp_0x27depr;
    interp_jump_table[table_sbpf_version][0x2f] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x2f : &&interp_0x2fdepr;

    interp_jump_table[table_sbpf_version][0x79] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x9c;
    interp_jump_table[table_sbpf_version][0x7a] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x97;
    interp_jump_table[table_sbpf_version][0x7b] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x9f;
    interp_jump_table[table_sbpf_version][0x9c] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x9c : &&interp_0x9cdepr;
    interp_jump_table[table_sbpf_version][0x97] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x97 : &&interp_0x97depr;
    interp_jump_table[table_sbpf_version][0x9f] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x9f : &&interp_0x9fdepr;

    interp_jump_table[table_sbpf_version][0x36] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x36 : &&sigill;
    interp_jump_table[table_sbpf_version][0x3e] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x3e : &&sigill;

    interp_jump_table[table_sbpf_version][0x46] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x46 : &&sigill;
    interp_jump_table[table_sbpf_version][0x4e] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x4e : &&sigill;
    interp_jump_table[table_sbpf_version][0x56] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x56 : &&sigill;
    interp_jump_table[table_sbpf_version][0x5e] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x5e : &&sigill;
    interp_jump_table[table_sbpf_version][0x66] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x66 : &&sigill;
    interp_jump_table[table_sbpf_version][0x6e] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x6e : &&sigill;
    interp_jump_table[table_sbpf_version][0x76] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x76 : &&sigill;
    interp_jump_table[table_sbpf_version][0x7e] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x7e : &&sigill;

    interp_jump_table[table_sbpf_version][0x86] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x86 : &&sigill;
    interp_jump_table[table_sbpf_version][0x8e] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x8e : &&sigill;
    interp_jump_table[table_sbpf_version][0x96] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x96 : &&sigill;
    interp_jump_table[table_sbpf_version][0x9e] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x9e : &&sigill;
    interp_jump_table[table_sbpf_version][0xb6] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xb6 : &&sigill;
    interp_jump_table[table_sbpf_version][0xbe] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xbe : &&sigill;

    interp_jump_table[table_sbpf_version][0xc6] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xc6 : &&sigill;
    interp_jump_table[table_sbpf_version][0xce] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xce : &&sigill;
    interp_jump_table[table_sbpf_version][0xd6] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xd6 : &&sigill;
    interp_jump_table[table_sbpf_version][0xde] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xde : &&sigill;
    interp_jump_table[table_sbpf_version][0xe6] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xe6 : &&sigill;
    interp_jump_table[table_sbpf_version][0xee] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xee : &&sigill;
    interp_jump_table[table_sbpf_version][0xf6] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xf6 : &&sigill;
    interp_jump_table[table_sbpf_version][0xfe] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xfe : &&sigill;

    interp_jump_table[table_sbpf_version][0x24] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x24;
    interp_jump_table[table_sbpf_version][0x34] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x34;
    interp_jump_table[table_sbpf_version][0x94] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x94;

    interp_jump_table[table_sbpf_version][0x84] =
        (table_sbpf_version < (2UL)) ? &&interp_0x84 : &&sigill;

    interp_jump_table[table_sbpf_version][0x04] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x04 : &&interp_0x04depr;
    interp_jump_table[table_sbpf_version][0x0c] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x0c : &&interp_0x0cdepr;
    interp_jump_table[table_sbpf_version][0x1c] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x1c : &&interp_0x1cdepr;
    interp_jump_table[table_sbpf_version][0xbc] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xbc : &&interp_0xbcdepr;
    interp_jump_table[table_sbpf_version][0x14] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x14 : &&interp_0x14depr;
    interp_jump_table[table_sbpf_version][0x17] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x17 : &&interp_0x17depr;

    interp_jump_table[table_sbpf_version][0x85] =
        (table_sbpf_version >= (3UL)) ? &&interp_0x85 : &&interp_0x85depr;
    interp_jump_table[table_sbpf_version][0x95] =
        (table_sbpf_version >= (3UL)) ? &&interp_0x95 : &&interp_0x9d;
    interp_jump_table[table_sbpf_version][0x9d] =
        (table_sbpf_version >= (3UL)) ? &&interp_0x9d : &&sigill;

    interp_jump_table[table_sbpf_version][0x8d] =
        (table_sbpf_version >= (3UL)) ? &&interp_0x8d : &&interp_0x8ddepr;
  }

  ulong pc = vm->pc;
  ulong ic = vm->ic;
  ulong cu = vm->cu;
  ulong frame_cnt = vm->frame_cnt;
  // # 142 "src/flamenco/vm/fd_vm_interp_core.c"
  ulong instr;
  ulong opcode;
  ulong dst;
  ulong src;
  ulong offset;
  uint imm;
  ulong reg_dst;
  ulong reg_src;
  // # 309 "src/flamenco/vm/fd_vm_interp_core.c"
  ulong pc0 = pc;
  ulong ic_correction = 0UL;
  // # 374 "src/flamenco/vm/fd_vm_interp_core.c"
  goto interp_exec;
interp_exec:
  // # 385 "src/flamenco/vm/fd_vm_interp_core.c"
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x04:
  reg[dst] = (ulong)(uint)((int)reg_dst + (int)imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x04depr:
  reg[dst] = (ulong)(long)((int)reg_dst + (int)imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x05:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += offset;
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x07:
  reg[dst] = reg_dst + (ulong)(long)(int)imm;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x0c:
  reg[dst] = (ulong)(uint)((int)reg_dst + (int)reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x0cdepr:
  reg[dst] = (ulong)(long)((int)reg_dst + (int)reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x0f:
  reg[dst] = reg_dst + reg_src;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x14:
  reg[dst] = (ulong)(uint)((int)imm - (int)reg_dst);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x14depr:
  reg[dst] = (ulong)(long)((int)reg_dst - (int)imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x15:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst == (ulong)(long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x17:
  reg[dst] = (ulong)(long)(int)imm - reg_dst;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x17depr:
  reg[dst] = reg_dst - (ulong)(long)(int)imm;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x18:
  pc++;
  ic_correction++;

  reg[dst] = (ulong)((ulong)imm | ((ulong)fd_vm_instr_imm(text[pc]) << 32));
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x1c:
  reg[dst] = (ulong)(uint)((int)reg_dst - (int)reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x1cdepr:
  reg[dst] = (ulong)(long)((int)reg_dst - (int)reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x1d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst == reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x1f:
  reg[dst] = reg_dst - reg_src;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x24:
  reg[dst] = (ulong)(long)((int)reg_dst * (int)imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x25:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst > (ulong)(long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x27: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(uchar), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  if (__builtin_expect(!!(!haddr), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);
    goto sigsegv;
  }
  fd_vm_mem_st_1(haddr, (uchar)imm);
}
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x2c: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_src + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(uchar), region_haddr,
                                region_ld_sz, 0, 0UL, &is_multi_region);
  if (__builtin_expect(!!(!haddr), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (1);
    goto sigsegv;
  }
  reg[dst] = fd_vm_mem_ld_1(haddr);
}
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x2d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst > reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x2f: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(uchar), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  if (__builtin_expect(!!(!haddr), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);
    goto sigsegv;
  }
  fd_vm_mem_st_1(haddr, (uchar)reg_src);
}
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x27depr:
  reg[dst] = (ulong)((long)reg_dst * (long)(int)imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x2cdepr:
  reg[dst] = (ulong)(long)((int)reg_dst * (int)reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x2fdepr:
  reg[dst] = reg_dst * reg_src;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x34:

  reg[dst] = (ulong)((uint)reg_dst / imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x35:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst >= (ulong)(long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x36:
  reg[dst] = (ulong)(((uint128)reg_dst * (uint128)(ulong)imm) >> 64);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x37: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(ushort), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);

    if (vm->direct_mapping) {

      ushort val = (ushort)imm;
      fd_vm_mem_st_try(vm, vaddr, sizeof(ushort), (uchar *)&val);
    }

    goto sigsegv;
  }
  fd_vm_mem_st_2(vm, vaddr, haddr, (ushort)imm, is_multi_region);
}
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x3c: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_src + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(ushort), region_haddr,
                                region_ld_sz, 0, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (1);
    goto sigsegv;
  }
  reg[dst] = fd_vm_mem_ld_2(vm, vaddr, haddr, is_multi_region);
}
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x3d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst >= reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x3f: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(ushort), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);

    if (vm->direct_mapping) {

      ushort val = (ushort)reg_src;
      fd_vm_mem_st_try(vm, vaddr, sizeof(ushort), (uchar *)&val);
    }

    goto sigsegv;
  }
  fd_vm_mem_st_2(vm, vaddr, haddr, (ushort)reg_src, is_multi_region);
}
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x3e:
  reg[dst] = (ulong)(((uint128)reg_dst * (uint128)reg_src) >> 64);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x37depr:
  reg[dst] = reg_dst / (ulong)(long)(int)imm;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x3cdepr:
  if (__builtin_expect(!!(!(uint)reg_src), 0L))
    goto sigfpe;
  reg[dst] = (ulong)((uint)reg_dst / (uint)reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x3fdepr:
  if (__builtin_expect(!!(!reg_src), 0L))
    goto sigfpe;
  reg[dst] = reg_dst / reg_src;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x44:
  reg[dst] = (ulong)((uint)reg_dst | imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x45:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(!!(reg_dst & (ulong)(long)(int)imm), offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x46:
  reg[dst] = (ulong)((uint)reg_dst / (uint)imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x47:
  reg[dst] = reg_dst | (ulong)(long)(int)imm;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x4c:
  reg[dst] = (ulong)(uint)(reg_dst | reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x4d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(!!(reg_dst & reg_src), offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x4e:
  if (__builtin_expect(!!(!(uint)reg_src), 0L))
    goto sigfpe;
  reg[dst] = (ulong)((uint)reg_dst / (uint)reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x4f:
  reg[dst] = reg_dst | reg_src;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x54:
  reg[dst] = (ulong)((uint)reg_dst & imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x55:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst != (ulong)(long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x56:
  reg[dst] = reg_dst / (ulong)imm;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x57:
  reg[dst] = reg_dst & (ulong)(long)(int)imm;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x5c:
  reg[dst] = (ulong)(uint)(reg_dst & reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x5d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst != reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x5e:
  if (__builtin_expect(!!(!reg_src), 0L))
    goto sigfpe;
  reg[dst] = reg_dst / reg_src;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x5f:
  reg[dst] = reg_dst & reg_src;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x64:

  reg[dst] = (ulong)(((uint)reg_dst << ((uint)imm & (31))));
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x65:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst > (long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x66:
  reg[dst] = (ulong)((uint)reg_dst % (uint)imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x67:

  reg[dst] = (reg_dst << (imm & (63)));
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x6c:

  reg[dst] = (ulong)(((uint)reg_dst << (reg_src & (31))));
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x6d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst > (long)reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x6e:
  if (__builtin_expect(!!(!(uint)reg_src), 0L))
    goto sigfpe;
  reg[dst] = (ulong)((uint)reg_dst % (uint)reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x6f:

  reg[dst] = (reg_dst << (reg_src & (63)));
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x74:

  reg[dst] = (ulong)(((uint)reg_dst >> (imm & (31))));
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x75:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst >= (long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x76:
  reg[dst] = reg_dst % (ulong)imm;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x77:

  reg[dst] = (reg_dst >> (imm & (63)));
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x7c:

  reg[dst] = (ulong)(((uint)reg_dst >> ((uint)reg_src & (31))));
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x7d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst >= (long)reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x7e:
  if (__builtin_expect(!!(!reg_src), 0L))
    goto sigfpe;
  reg[dst] = reg_dst % reg_src;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x7f:

  reg[dst] = (reg_dst >> (reg_src & (63)));
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x84:
  reg[dst] = (ulong)(-(uint)reg_dst);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x85:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;

  shadow[frame_cnt].r6 = reg[6];
  shadow[frame_cnt].r7 = reg[7];
  shadow[frame_cnt].r8 = reg[8];
  shadow[frame_cnt].r9 = reg[9];
  shadow[frame_cnt].r10 = reg[10];
  shadow[frame_cnt].pc = pc;
  if (__builtin_expect(!!(++frame_cnt >= frame_max), 0L))
    goto sigstack;
  if (!(sbpf_version >= (1UL)))
    reg[10] += vm->stack_frame_size;
  ;
  pc = (ulong)((long)pc + (long)(int)imm);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x85depr:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  {

    fd_sbpf_syscalls_t const *syscall =
        imm != fd_sbpf_syscalls_key_null()
            ? fd_sbpf_syscalls_query_const(
                  syscalls, (ulong)imm,
                  // # 792 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                  ((void *)0)
                  // # 792 "src/flamenco/vm/fd_vm_interp_core.c"
                  )
            :
            // # 792 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
            ((void *)0)
        // # 792 "src/flamenco/vm/fd_vm_interp_core.c"
        ;
    if (__builtin_expect(!!(!syscall), 0L)) {
      // # 819 "src/flamenco/vm/fd_vm_interp_core.c"
      if (__builtin_expect(!!(imm == 0x71e3cf81U), 0L)) {
        shadow[frame_cnt].r6 = reg[6];
        shadow[frame_cnt].r7 = reg[7];
        shadow[frame_cnt].r8 = reg[8];
        shadow[frame_cnt].r9 = reg[9];
        shadow[frame_cnt].r10 = reg[10];
        shadow[frame_cnt].pc = pc;
        if (__builtin_expect(!!(++frame_cnt >= frame_max), 0L))
          goto sigstack;
        if (!(sbpf_version >= (1UL)))
          reg[10] += vm->stack_frame_size;
        ;
        pc = entry_pc - 1;
      } else {
        ulong target_pc = (ulong)fd_pchash_inverse(imm);
        if (__builtin_expect(!!(target_pc >= text_cnt), 0L)) {
          goto sigillbr;
        }
        if (__builtin_expect(!!(!fd_sbpf_calldests_test(calldests, target_pc)),
                             0L)) {
          goto sigillbr;
        }
        shadow[frame_cnt].r6 = reg[6];
        shadow[frame_cnt].r7 = reg[7];
        shadow[frame_cnt].r8 = reg[8];
        shadow[frame_cnt].r9 = reg[9];
        shadow[frame_cnt].r10 = reg[10];
        shadow[frame_cnt].pc = pc;
        if (__builtin_expect(!!(++frame_cnt >= frame_max), 0L))
          goto sigstack;
        if (!(sbpf_version >= (1UL)))
          reg[10] += vm->stack_frame_size;
        ;
        pc = target_pc - 1;
      }

    } else {

      vm->pc = pc;
      vm->ic = ic;
      vm->cu = cu;
      vm->frame_cnt = frame_cnt;
      if (__builtin_expect(!!(vm->dump_syscall_to_pb), 0L)) {
        fd_dump_vm_syscall_to_protobuf(vm, syscall->name);
      }
      ulong ret[1];
      err = syscall->func(vm, reg[1], reg[2], reg[3], reg[4], reg[5], ret);
      reg[0] = ret[0];
      ulong cu_req = vm->cu;
      cu = fd_ulong_min(cu_req, cu);
      if (__builtin_expect(!!(err), 0L)) {
        if (err == (-24))
          cu = 0UL;
        ((void)0);
        goto sigsyscall;
      };
    }
  }
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x86:
  reg[dst] = (ulong)((uint)reg_dst * imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x87: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(uint), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);

    if (vm->direct_mapping) {

      uint val = (uint)imm;
      fd_vm_mem_st_try(vm, vaddr, sizeof(uint), (uchar *)&val);
    }

    goto sigsegv;
  }
  fd_vm_mem_st_4(vm, vaddr, haddr, imm, is_multi_region);
}
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x87depr:
  reg[dst] = -reg_dst;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x8c: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_src + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(uint), region_haddr,
                                region_ld_sz, 0, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (1);
    goto sigsegv;
  }
  reg[dst] = fd_vm_mem_ld_4(vm, vaddr, haddr, is_multi_region);
}
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x8d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  {
    shadow[frame_cnt].r6 = reg[6];
    shadow[frame_cnt].r7 = reg[7];
    shadow[frame_cnt].r8 = reg[8];
    shadow[frame_cnt].r9 = reg[9];
    shadow[frame_cnt].r10 = reg[10];
    shadow[frame_cnt].pc = pc;
    if (__builtin_expect(!!(++frame_cnt >= frame_max), 0L))
      goto sigstack;
    if (!(sbpf_version >= (1UL)))
      reg[10] += vm->stack_frame_size;
    ;
    ulong target_pc = (reg_src - vm->text_off) / 8UL;
    if (__builtin_expect(!!(target_pc >= text_cnt), 0L))
      goto sigtextbr;
    if (__builtin_expect(!!(!fd_sbpf_calldests_test(calldests, target_pc)),
                         0L)) {
      goto sigillbr;
    }
    pc = target_pc - 1;
  }
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x8ddepr:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  {

    shadow[frame_cnt].r6 = reg[6];
    shadow[frame_cnt].r7 = reg[7];
    shadow[frame_cnt].r8 = reg[8];
    shadow[frame_cnt].r9 = reg[9];
    shadow[frame_cnt].r10 = reg[10];
    shadow[frame_cnt].pc = pc;
    if (__builtin_expect(!!(++frame_cnt >= frame_max), 0L))
      goto sigstack;
    if (!(sbpf_version >= (1UL)))
      reg[10] += vm->stack_frame_size;
    ;

    ulong vaddr = (sbpf_version >= (2UL)) ? reg_src : reg[imm & 15U];

    ulong region = vaddr >> 32;

    ulong target_pc = ((vaddr & (0xffffffffUL)) - vm->text_off) / 8UL;
    if (__builtin_expect(!!((region != 1UL) | (target_pc >= text_cnt)), 0L))
      goto sigtextbr;
    pc = target_pc - 1;
  }
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x8e:
  reg[dst] = (ulong)((uint)reg_dst * (uint)reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x8f: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(uint), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);

    if (vm->direct_mapping) {

      uint val = (uint)reg_src;
      fd_vm_mem_st_try(vm, vaddr, sizeof(uint), (uchar *)&val);
    }

    goto sigsegv;
  }
  fd_vm_mem_st_4(vm, vaddr, haddr, (uint)reg_src, is_multi_region);
}
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x94:
  reg[dst] = (ulong)((uint)reg_dst % imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x95:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  {

    fd_sbpf_syscalls_t const *syscall = fd_sbpf_syscalls_query_const(
        syscalls, (ulong)imm,
        // # 945 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
        ((void *)0)
        // # 945 "src/flamenco/vm/fd_vm_interp_core.c"
    );
    if (__builtin_expect(!!(!syscall), 0L))
      goto sigillbr;

    vm->pc = pc;
    vm->ic = ic;
    vm->cu = cu;
    vm->frame_cnt = frame_cnt;
    if (__builtin_expect(!!(vm->dump_syscall_to_pb), 0L)) {
      fd_dump_vm_syscall_to_protobuf(vm, syscall->name);
    }
    ulong ret[1];
    err = syscall->func(vm, reg[1], reg[2], reg[3], reg[4], reg[5], ret);
    reg[0] = ret[0];
    ulong cu_req = vm->cu;
    cu = fd_ulong_min(cu_req, cu);
    if (__builtin_expect(!!(err), 0L)) {
      if (err == (-24))
        cu = 0UL;
      ((void)0);
      goto sigsyscall;
    };
  }
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x96:
  reg[dst] = reg_dst * (ulong)(long)(int)imm;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x97: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(ulong), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);

    if (vm->direct_mapping) {

      ulong val = (ulong)(long)(int)imm;
      fd_vm_mem_st_try(vm, vaddr, sizeof(ulong), (uchar *)&val);
    }

    goto sigsegv;
  }
  fd_vm_mem_st_8(vm, vaddr, haddr, (ulong)(long)(int)imm, is_multi_region);
}
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x9c: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_src + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(ulong), region_haddr,
                                region_ld_sz, 0, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (1);
    goto sigsegv;
  }
  reg[dst] = fd_vm_mem_ld_8(vm, vaddr, haddr, is_multi_region);
}
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x9d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;

  if (__builtin_expect(!!(!frame_cnt), 0L))
    goto sigexit;
  frame_cnt--;
  reg[6] = shadow[frame_cnt].r6;
  reg[7] = shadow[frame_cnt].r7;
  reg[8] = shadow[frame_cnt].r8;
  reg[9] = shadow[frame_cnt].r9;
  reg[10] = shadow[frame_cnt].r10;
  pc = shadow[frame_cnt].pc;
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x9e:
  reg[dst] = reg_dst * reg_src;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x9f: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(ulong), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);

    if (vm->direct_mapping) {

      fd_vm_mem_st_try(vm, vaddr, sizeof(ulong), (uchar *)&reg_src);
    }

    goto sigsegv;
  }
  fd_vm_mem_st_8(vm, vaddr, haddr, reg_src, is_multi_region);
}
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x97depr:
  reg[dst] = reg_dst % (ulong)(long)(int)imm;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x9cdepr:
  if (__builtin_expect(!!(!(uint)reg_src), 0L))
    goto sigfpe;
  reg[dst] = (ulong)(((uint)reg_dst % (uint)reg_src));
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x9fdepr:
  if (__builtin_expect(!!(!reg_src), 0L))
    goto sigfpe;
  reg[dst] = reg_dst % reg_src;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xa4:
  reg[dst] = (ulong)((uint)reg_dst ^ imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xa5:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst < (ulong)(long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xa7:
  reg[dst] = reg_dst ^ (ulong)(long)(int)imm;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xac:
  reg[dst] = (ulong)(uint)(reg_dst ^ reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xad:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst < reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xaf:
  reg[dst] = reg_dst ^ reg_src;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xb4:
  reg[dst] = (ulong)imm;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xb5:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst <= (ulong)(long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xb6:
  reg[dst] = (ulong)(((int128)(long)reg_dst * (int128)(long)(int)imm) >> 64);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xb7:
  reg[dst] = (ulong)(long)(int)imm;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xbc:
  reg[dst] = (ulong)(long)(int)reg_src;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xbcdepr:
  reg[dst] = (ulong)(uint)reg_src;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xbd:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst <= reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xbe:
  reg[dst] = (ulong)(((int128)(long)reg_dst * (int128)(long)reg_src) >> 64);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xbf:
  reg[dst] = reg_src;
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xc4:
  reg[dst] = (ulong)(uint)((int)reg_dst >> imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xc5:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst < (long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xc6:
  if (__builtin_expect(!!(((int)reg_dst ==
                           // # 1120 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffff - 1)
                           // # 1120 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((int)imm == -1)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)(uint)((int)reg_dst / (int)imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xc7:
  reg[dst] = (ulong)((long)reg_dst >> imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xcc:
  reg[dst] = (ulong)(uint)((int)reg_dst >> (uint)reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xcd:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst < (long)reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xce:
  if (__builtin_expect(!!(!(int)reg_src), 0L))
    goto sigfpe;
  if (__builtin_expect(!!(((int)reg_dst ==
                           // # 1138 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffff - 1)
                           // # 1138 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((int)reg_src == -1)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)(uint)((int)reg_dst / (int)reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xcf:
  reg[dst] = (ulong)((long)reg_dst >> reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xd4:
  switch (imm) {
  case 16U:
    reg[dst] = (ushort)reg_dst;
    break;
  case 32U:
    reg[dst] = (uint)reg_dst;
    break;
  case 64U:
    break;
  default:
    goto siginv;
  }
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xd5:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst <= (long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xd6:
  if (__builtin_expect(!!(((long)reg_dst ==
                           // # 1162 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffffffffffffL - 1L)
                           // # 1162 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((long)(int)imm == -1L)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)((long)reg_dst / (long)(int)imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xdc:
  switch (imm) {
  case 16U:
    reg[dst] = (ulong)fd_ushort_bswap((ushort)reg_dst);
    break;
  case 32U:
    reg[dst] = (ulong)fd_uint_bswap((uint)reg_dst);
    break;
  case 64U:
    reg[dst] = fd_ulong_bswap((ulong)reg_dst);
    break;
  default:
    goto siginv;
  }
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xdd:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst <= (long)reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xde:
  if (__builtin_expect(!!(!reg_src), 0L))
    goto sigfpe;
  if (__builtin_expect(!!(((long)reg_dst ==
                           // # 1181 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffffffffffffL - 1L)
                           // # 1181 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((long)reg_src == -1L)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)((long)reg_dst / (long)reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xe6:
  if (__builtin_expect(!!(((int)reg_dst ==
                           // # 1188 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffff - 1)
                           // # 1188 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((int)imm == -1)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)(uint)((int)reg_dst % (int)imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xee:
  if (__builtin_expect(!!(!(int)reg_src), 0L))
    goto sigfpe;
  if (__builtin_expect(!!(((int)reg_dst ==
                           // # 1194 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffff - 1)
                           // # 1194 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((int)reg_src == -1)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)(uint)((int)reg_dst % (int)reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xf6:
  if (__builtin_expect(!!(((long)reg_dst ==
                           // # 1201 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffffffffffffL - 1L)
                           // # 1201 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((long)(int)imm == -1L)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)((long)reg_dst % (long)(int)imm);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xf7:
  reg[dst] = reg_dst | (((ulong)imm) << 32);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0xfe:
  if (__builtin_expect(!!(!reg_src), 0L))
    goto sigfpe;
  if (__builtin_expect(!!(((long)reg_dst ==
                           // # 1211 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffffffffffffL - 1L)
                           // # 1211 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((long)reg_src == -1L)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)((long)reg_dst % (long)reg_src);
  pc++;
  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];
// # 1246 "src/flamenco/vm/fd_vm_interp_core.c"
sigtext:
  err = (-7);
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    err = (-9);
  cu -= fd_ulong_min(ic_correction, cu);
  goto interp_halt;
sigtextbr:
  err = (-8);
  goto interp_halt;
sigstack:
  err = (-3);
  goto interp_halt;
sigill:
  err = (-16);
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    err = (-9);
  cu -= fd_ulong_min(ic_correction, cu);
  goto interp_halt;
sigillbr:
  err = (-16);
  goto interp_halt;
siginv:
  err = (-15);
  goto interp_halt;
sigsegv:
  err = fd_vm_generate_access_violation(vm->segv_vaddr, vm->sbpf_version);
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    err = (-9);
  cu -= fd_ulong_min(ic_correction, cu);
  goto interp_halt;
sigcost:
  err = (-9);
  cu = 0UL;
  goto interp_halt;
sigsyscall:
  err = (-20);
  goto interp_halt;
sigfpe:
  err = (-5);
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    err = (-9);
  cu -= fd_ulong_min(ic_correction, cu);
  goto interp_halt;
sigfpeof:
  err = (-6);
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    err = (-9);
  cu -= fd_ulong_min(ic_correction, cu);
  goto interp_halt;
sigexit:
  goto interp_halt;

interp_halt:

  vm->pc = pc;
  vm->ic = ic;
  vm->cu = cu;
  vm->frame_cnt = frame_cnt;
// # 1285 "src/flamenco/vm/fd_vm_interp_core.c"
#pragma GCC diagnostic pop
  // # 35 "src/flamenco/vm/fd_vm_interp.c" 2

  return err;
}

int fd_vm_exec_trace(fd_vm_t *vm) {

  ulong frame_max = (64UL);

  ulong const *restrict text = vm->text;
  ulong text_cnt = vm->text_cnt;
  ulong entry_pc = vm->entry_pc;
  ulong const *restrict calldests = vm->calldests;

  fd_sbpf_syscalls_t const *restrict syscalls = vm->syscalls;

  ulong const *restrict region_haddr = vm->region_haddr;
  uint const *restrict region_ld_sz = vm->region_ld_sz;
  uint const *restrict region_st_sz = vm->region_st_sz;

  ulong *restrict reg = vm->reg;

  fd_vm_shadow_t *restrict shadow = vm->shadow;

  int err = (0);

// # 1 "src/flamenco/vm/fd_vm_interp_core.c" 1
// # 12 "src/flamenco/vm/fd_vm_interp_core.c"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
  // # 24 "src/flamenco/vm/fd_vm_interp_core.c"
  // # 1 "src/flamenco/vm/fd_vm_interp_jump_table.c" 1

  static void const *interp_jump_table[(4UL)][256] = {

      {
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x04, &&interp_0x05, &&sigill,      &&interp_0x07,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x0c, &&sigill,      &&sigill,      &&interp_0x0f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x14, &&interp_0x15, &&sigill,      &&interp_0x17,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x1c, &&interp_0x1d, &&sigill,      &&interp_0x1f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x25, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x2d, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x35, &&interp_0x36, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x3d, &&interp_0x3e, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x44, &&interp_0x45, &&interp_0x46, &&interp_0x47,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x4c, &&interp_0x4d, &&interp_0x4e, &&interp_0x4f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x54, &&interp_0x55, &&interp_0x56, &&interp_0x57,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x5c, &&interp_0x5d, &&interp_0x5e, &&interp_0x5f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x64, &&interp_0x65, &&interp_0x66, &&interp_0x67,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x6c, &&interp_0x6d, &&interp_0x6e, &&interp_0x6f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x74, &&interp_0x75, &&interp_0x76, &&interp_0x77,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x7c, &&interp_0x7d, &&interp_0x7e, &&interp_0x7f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x85, &&interp_0x86, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x8c, &&interp_0x8d, &&interp_0x8e, &&interp_0x8f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x95, &&interp_0x96, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x9e, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xa4, &&interp_0xa5, &&sigill,      &&interp_0xa7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xac, &&interp_0xad, &&sigill,      &&interp_0xaf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xb4, &&interp_0xb5, &&interp_0xb6, &&interp_0xb7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xbc, &&interp_0xbd, &&interp_0xbe, &&interp_0xbf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xc4, &&interp_0xc5, &&interp_0xc6, &&interp_0xc7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xcc, &&interp_0xcd, &&interp_0xce, &&interp_0xcf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0xd5, &&interp_0xd6, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xdc, &&interp_0xdd, &&interp_0xde, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xe6, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xee, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xf6, &&interp_0xf7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xfe, &&sigill,
      },
      {

          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x04, &&interp_0x05, &&sigill,      &&interp_0x07,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x0c, &&sigill,      &&sigill,      &&interp_0x0f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x14, &&interp_0x15, &&sigill,      &&interp_0x17,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x1c, &&interp_0x1d, &&sigill,      &&interp_0x1f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x25, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x2d, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x35, &&interp_0x36, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x3d, &&interp_0x3e, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x44, &&interp_0x45, &&interp_0x46, &&interp_0x47,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x4c, &&interp_0x4d, &&interp_0x4e, &&interp_0x4f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x54, &&interp_0x55, &&interp_0x56, &&interp_0x57,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x5c, &&interp_0x5d, &&interp_0x5e, &&interp_0x5f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x64, &&interp_0x65, &&interp_0x66, &&interp_0x67,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x6c, &&interp_0x6d, &&interp_0x6e, &&interp_0x6f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x74, &&interp_0x75, &&interp_0x76, &&interp_0x77,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x7c, &&interp_0x7d, &&interp_0x7e, &&interp_0x7f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x85, &&interp_0x86, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x8c, &&interp_0x8d, &&interp_0x8e, &&interp_0x8f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x95, &&interp_0x96, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x9e, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xa4, &&interp_0xa5, &&sigill,      &&interp_0xa7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xac, &&interp_0xad, &&sigill,      &&interp_0xaf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xb4, &&interp_0xb5, &&interp_0xb6, &&interp_0xb7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xbc, &&interp_0xbd, &&interp_0xbe, &&interp_0xbf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xc4, &&interp_0xc5, &&interp_0xc6, &&interp_0xc7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xcc, &&interp_0xcd, &&interp_0xce, &&interp_0xcf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0xd5, &&interp_0xd6, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xdc, &&interp_0xdd, &&interp_0xde, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xe6, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xee, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xf6, &&interp_0xf7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xfe, &&sigill,
      },
      {

          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x04, &&interp_0x05, &&sigill,      &&interp_0x07,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x0c, &&sigill,      &&sigill,      &&interp_0x0f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x14, &&interp_0x15, &&sigill,      &&interp_0x17,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x1c, &&interp_0x1d, &&sigill,      &&interp_0x1f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x25, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x2d, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x35, &&interp_0x36, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x3d, &&interp_0x3e, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x44, &&interp_0x45, &&interp_0x46, &&interp_0x47,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x4c, &&interp_0x4d, &&interp_0x4e, &&interp_0x4f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x54, &&interp_0x55, &&interp_0x56, &&interp_0x57,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x5c, &&interp_0x5d, &&interp_0x5e, &&interp_0x5f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x64, &&interp_0x65, &&interp_0x66, &&interp_0x67,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x6c, &&interp_0x6d, &&interp_0x6e, &&interp_0x6f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x74, &&interp_0x75, &&interp_0x76, &&interp_0x77,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x7c, &&interp_0x7d, &&interp_0x7e, &&interp_0x7f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x85, &&interp_0x86, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0x8c, &&interp_0x8d, &&interp_0x8e, &&interp_0x8f,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x95, &&interp_0x96, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x9e, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xa4, &&interp_0xa5, &&sigill,      &&interp_0xa7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xac, &&interp_0xad, &&sigill,      &&interp_0xaf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xb4, &&interp_0xb5, &&interp_0xb6, &&interp_0xb7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xbc, &&interp_0xbd, &&interp_0xbe, &&interp_0xbf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xc4, &&interp_0xc5, &&interp_0xc6, &&interp_0xc7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xcc, &&interp_0xcd, &&interp_0xce, &&interp_0xcf,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0xd5, &&interp_0xd6, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&interp_0xdc, &&interp_0xdd, &&interp_0xde, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xe6, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xee, &&sigill,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xf6, &&interp_0xf7,
          &&sigill,      &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xfe, &&sigill,
      },
      {

          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x04, &&interp_0x05,
          &&sigill,      &&interp_0x07, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0x0c, &&sigill,      &&sigill,
          &&interp_0x0f, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x14,
          &&interp_0x15, &&sigill,      &&interp_0x17,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x1c, &&interp_0x1d,
          &&sigill,      &&interp_0x1f, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x25, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0x2d, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x35,
          &&interp_0x36, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x3d, &&interp_0x3e,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x44,
          &&interp_0x45, &&interp_0x46, &&interp_0x47,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x4c, &&interp_0x4d,
          &&interp_0x4e, &&interp_0x4f, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0x54, &&interp_0x55, &&interp_0x56,
          &&interp_0x57, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x5c,
          &&interp_0x5d, &&interp_0x5e, &&interp_0x5f,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x64, &&interp_0x65,
          &&interp_0x66, &&interp_0x67, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0x6c, &&interp_0x6d, &&interp_0x6e,
          &&interp_0x6f, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x74,
          &&interp_0x75, &&interp_0x76, &&interp_0x77,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x7c, &&interp_0x7d,
          &&interp_0x7e, &&interp_0x7f, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0x85, &&interp_0x86,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x8c,
          &&interp_0x8d, &&interp_0x8e, &&interp_0x8f,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x95,
          &&interp_0x96, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0x9e,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xa4,
          &&interp_0xa5, &&sigill,      &&interp_0xa7,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0xac, &&interp_0xad,
          &&sigill,      &&interp_0xaf, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0xb4, &&interp_0xb5, &&interp_0xb6,
          &&interp_0xb7, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xbc,
          &&interp_0xbd, &&interp_0xbe, &&interp_0xbf,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0xc4, &&interp_0xc5,
          &&interp_0xc6, &&interp_0xc7, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0xcc, &&interp_0xcd, &&interp_0xce,
          &&interp_0xcf, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0xd5, &&interp_0xd6, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0xdc, &&interp_0xdd,
          &&interp_0xde, &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xe6,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&interp_0xee, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&interp_0xf6, &&interp_0xf7, &&sigill,
          &&sigill,      &&sigill,      &&sigill,
          &&sigill,      &&sigill,      &&interp_0xfe,
          &&sigill

      }};
  // # 25 "src/flamenco/vm/fd_vm_interp_core.c" 2

  ulong sbpf_version = vm->sbpf_version;

  for (ulong table_sbpf_version = 0UL; table_sbpf_version < (4UL);
       table_sbpf_version++) {

    interp_jump_table[table_sbpf_version][0x18] =
        (table_sbpf_version < (2UL)) ? &&interp_0x18 : &&sigill;
    interp_jump_table[table_sbpf_version][0xf7] =
        (table_sbpf_version < (2UL)) ? &&sigill : &&interp_0xf7;

    interp_jump_table[table_sbpf_version][0xd4] =
        (table_sbpf_version < (2UL)) ? &&interp_0xd4 : &&sigill;

    interp_jump_table[table_sbpf_version][0x61] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x8c;
    interp_jump_table[table_sbpf_version][0x62] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x87;
    interp_jump_table[table_sbpf_version][0x63] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x8f;
    interp_jump_table[table_sbpf_version][0x8c] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x8c : &&sigill;
    interp_jump_table[table_sbpf_version][0x87] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x87 : &&interp_0x87depr;
    interp_jump_table[table_sbpf_version][0x8f] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x8f : &&sigill;

    interp_jump_table[table_sbpf_version][0x69] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x3c;
    interp_jump_table[table_sbpf_version][0x6a] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x37;
    interp_jump_table[table_sbpf_version][0x6b] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x3f;
    interp_jump_table[table_sbpf_version][0x3c] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x3c : &&interp_0x3cdepr;
    interp_jump_table[table_sbpf_version][0x37] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x37 : &&interp_0x37depr;
    interp_jump_table[table_sbpf_version][0x3f] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x3f : &&interp_0x3fdepr;

    interp_jump_table[table_sbpf_version][0x71] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x2c;
    interp_jump_table[table_sbpf_version][0x72] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x27;
    interp_jump_table[table_sbpf_version][0x73] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x2f;
    interp_jump_table[table_sbpf_version][0x2c] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x2c : &&interp_0x2cdepr;
    interp_jump_table[table_sbpf_version][0x27] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x27 : &&interp_0x27depr;
    interp_jump_table[table_sbpf_version][0x2f] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x2f : &&interp_0x2fdepr;

    interp_jump_table[table_sbpf_version][0x79] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x9c;
    interp_jump_table[table_sbpf_version][0x7a] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x97;
    interp_jump_table[table_sbpf_version][0x7b] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x9f;
    interp_jump_table[table_sbpf_version][0x9c] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x9c : &&interp_0x9cdepr;
    interp_jump_table[table_sbpf_version][0x97] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x97 : &&interp_0x97depr;
    interp_jump_table[table_sbpf_version][0x9f] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x9f : &&interp_0x9fdepr;

    interp_jump_table[table_sbpf_version][0x36] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x36 : &&sigill;
    interp_jump_table[table_sbpf_version][0x3e] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x3e : &&sigill;

    interp_jump_table[table_sbpf_version][0x46] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x46 : &&sigill;
    interp_jump_table[table_sbpf_version][0x4e] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x4e : &&sigill;
    interp_jump_table[table_sbpf_version][0x56] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x56 : &&sigill;
    interp_jump_table[table_sbpf_version][0x5e] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x5e : &&sigill;
    interp_jump_table[table_sbpf_version][0x66] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x66 : &&sigill;
    interp_jump_table[table_sbpf_version][0x6e] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x6e : &&sigill;
    interp_jump_table[table_sbpf_version][0x76] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x76 : &&sigill;
    interp_jump_table[table_sbpf_version][0x7e] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x7e : &&sigill;

    interp_jump_table[table_sbpf_version][0x86] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x86 : &&sigill;
    interp_jump_table[table_sbpf_version][0x8e] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x8e : &&sigill;
    interp_jump_table[table_sbpf_version][0x96] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x96 : &&sigill;
    interp_jump_table[table_sbpf_version][0x9e] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x9e : &&sigill;
    interp_jump_table[table_sbpf_version][0xb6] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xb6 : &&sigill;
    interp_jump_table[table_sbpf_version][0xbe] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xbe : &&sigill;

    interp_jump_table[table_sbpf_version][0xc6] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xc6 : &&sigill;
    interp_jump_table[table_sbpf_version][0xce] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xce : &&sigill;
    interp_jump_table[table_sbpf_version][0xd6] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xd6 : &&sigill;
    interp_jump_table[table_sbpf_version][0xde] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xde : &&sigill;
    interp_jump_table[table_sbpf_version][0xe6] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xe6 : &&sigill;
    interp_jump_table[table_sbpf_version][0xee] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xee : &&sigill;
    interp_jump_table[table_sbpf_version][0xf6] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xf6 : &&sigill;
    interp_jump_table[table_sbpf_version][0xfe] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xfe : &&sigill;

    interp_jump_table[table_sbpf_version][0x24] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x24;
    interp_jump_table[table_sbpf_version][0x34] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x34;
    interp_jump_table[table_sbpf_version][0x94] =
        (table_sbpf_version >= (2UL)) ? &&sigill : &&interp_0x94;

    interp_jump_table[table_sbpf_version][0x84] =
        (table_sbpf_version < (2UL)) ? &&interp_0x84 : &&sigill;

    interp_jump_table[table_sbpf_version][0x04] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x04 : &&interp_0x04depr;
    interp_jump_table[table_sbpf_version][0x0c] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x0c : &&interp_0x0cdepr;
    interp_jump_table[table_sbpf_version][0x1c] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x1c : &&interp_0x1cdepr;
    interp_jump_table[table_sbpf_version][0xbc] =
        (table_sbpf_version >= (2UL)) ? &&interp_0xbc : &&interp_0xbcdepr;
    interp_jump_table[table_sbpf_version][0x14] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x14 : &&interp_0x14depr;
    interp_jump_table[table_sbpf_version][0x17] =
        (table_sbpf_version >= (2UL)) ? &&interp_0x17 : &&interp_0x17depr;

    interp_jump_table[table_sbpf_version][0x85] =
        (table_sbpf_version >= (3UL)) ? &&interp_0x85 : &&interp_0x85depr;
    interp_jump_table[table_sbpf_version][0x95] =
        (table_sbpf_version >= (3UL)) ? &&interp_0x95 : &&interp_0x9d;
    interp_jump_table[table_sbpf_version][0x9d] =
        (table_sbpf_version >= (3UL)) ? &&interp_0x9d : &&sigill;

    interp_jump_table[table_sbpf_version][0x8d] =
        (table_sbpf_version >= (3UL)) ? &&interp_0x8d : &&interp_0x8ddepr;
  }

  ulong pc = vm->pc;
  ulong ic = vm->ic;
  ulong cu = vm->cu;
  ulong frame_cnt = vm->frame_cnt;
  // # 142 "src/flamenco/vm/fd_vm_interp_core.c"
  ulong instr;
  ulong opcode;
  ulong dst;
  ulong src;
  ulong offset;
  uint imm;
  ulong reg_dst;
  ulong reg_src;
  // # 309 "src/flamenco/vm/fd_vm_interp_core.c"
  ulong pc0 = pc;
  ulong ic_correction = 0UL;
  // # 374 "src/flamenco/vm/fd_vm_interp_core.c"
  goto interp_exec;
interp_exec:

  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  fd_vm_trace_event_exe(vm->trace, pc, ic + (pc - pc0 - ic_correction), cu, reg,
                        vm->text + pc, vm->text_cnt - pc, ic_correction,
                        frame_cnt);

  if (__builtin_expect(!!(pc >= text_cnt), 0L))
    goto sigtext;
  instr = text[pc];
  opcode = fd_vm_instr_opcode(instr);
  dst = fd_vm_instr_dst(instr);
  src = fd_vm_instr_src(instr);
  offset = fd_vm_instr_offset(instr);
  imm = fd_vm_instr_imm(instr);
  reg_dst = reg[dst];
  reg_src = reg[src];
  goto *interp_jump_table[sbpf_version][opcode];

interp_0x04:
  reg[dst] = (ulong)(uint)((int)reg_dst + (int)imm);
  pc++;
  goto interp_exec;

interp_0x04depr:
  reg[dst] = (ulong)(long)((int)reg_dst + (int)imm);
  pc++;
  goto interp_exec;

interp_0x05:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += offset;
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x07:
  reg[dst] = reg_dst + (ulong)(long)(int)imm;
  pc++;
  goto interp_exec;

interp_0x0c:
  reg[dst] = (ulong)(uint)((int)reg_dst + (int)reg_src);
  pc++;
  goto interp_exec;

interp_0x0cdepr:
  reg[dst] = (ulong)(long)((int)reg_dst + (int)reg_src);
  pc++;
  goto interp_exec;

interp_0x0f:
  reg[dst] = reg_dst + reg_src;
  pc++;
  goto interp_exec;

interp_0x14:
  reg[dst] = (ulong)(uint)((int)imm - (int)reg_dst);
  pc++;
  goto interp_exec;

interp_0x14depr:
  reg[dst] = (ulong)(long)((int)reg_dst - (int)imm);
  pc++;
  goto interp_exec;

interp_0x15:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst == (ulong)(long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x17:
  reg[dst] = (ulong)(long)(int)imm - reg_dst;
  pc++;
  goto interp_exec;

interp_0x17depr:
  reg[dst] = reg_dst - (ulong)(long)(int)imm;
  pc++;
  goto interp_exec;

interp_0x18:
  pc++;
  ic_correction++;

  reg[dst] = (ulong)((ulong)imm | ((ulong)fd_vm_instr_imm(text[pc]) << 32));
  pc++;
  goto interp_exec;

interp_0x1c:
  reg[dst] = (ulong)(uint)((int)reg_dst - (int)reg_src);
  pc++;
  goto interp_exec;

interp_0x1cdepr:
  reg[dst] = (ulong)(long)((int)reg_dst - (int)reg_src);
  pc++;
  goto interp_exec;

interp_0x1d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst == reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x1f:
  reg[dst] = reg_dst - reg_src;
  pc++;
  goto interp_exec;

interp_0x24:
  reg[dst] = (ulong)(long)((int)reg_dst * (int)imm);
  pc++;
  goto interp_exec;

interp_0x25:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst > (ulong)(long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x27: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(uchar), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  if (__builtin_expect(!!(!haddr), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);
    goto sigsegv;
  }
  fd_vm_mem_st_1(haddr, (uchar)imm);
}
  pc++;
  goto interp_exec;

interp_0x2c: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_src + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(uchar), region_haddr,
                                region_ld_sz, 0, 0UL, &is_multi_region);
  if (__builtin_expect(!!(!haddr), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (1);
    goto sigsegv;
  }
  reg[dst] = fd_vm_mem_ld_1(haddr);
}
  pc++;
  goto interp_exec;

interp_0x2d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst > reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x2f: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(uchar), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  if (__builtin_expect(!!(!haddr), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);
    goto sigsegv;
  }
  fd_vm_mem_st_1(haddr, (uchar)reg_src);
}
  pc++;
  goto interp_exec;

interp_0x27depr:
  reg[dst] = (ulong)((long)reg_dst * (long)(int)imm);
  pc++;
  goto interp_exec;

interp_0x2cdepr:
  reg[dst] = (ulong)(long)((int)reg_dst * (int)reg_src);
  pc++;
  goto interp_exec;

interp_0x2fdepr:
  reg[dst] = reg_dst * reg_src;
  pc++;
  goto interp_exec;

interp_0x34:

  reg[dst] = (ulong)((uint)reg_dst / imm);
  pc++;
  goto interp_exec;

interp_0x35:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst >= (ulong)(long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x36:
  reg[dst] = (ulong)(((uint128)reg_dst * (uint128)(ulong)imm) >> 64);
  pc++;
  goto interp_exec;

interp_0x37: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(ushort), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);

    if (vm->direct_mapping) {

      ushort val = (ushort)imm;
      fd_vm_mem_st_try(vm, vaddr, sizeof(ushort), (uchar *)&val);
    }

    goto sigsegv;
  }
  fd_vm_mem_st_2(vm, vaddr, haddr, (ushort)imm, is_multi_region);
}
  pc++;
  goto interp_exec;

interp_0x3c: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_src + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(ushort), region_haddr,
                                region_ld_sz, 0, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (1);
    goto sigsegv;
  }
  reg[dst] = fd_vm_mem_ld_2(vm, vaddr, haddr, is_multi_region);
}
  pc++;
  goto interp_exec;

interp_0x3d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst >= reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x3f: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(ushort), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);

    if (vm->direct_mapping) {

      ushort val = (ushort)reg_src;
      fd_vm_mem_st_try(vm, vaddr, sizeof(ushort), (uchar *)&val);
    }

    goto sigsegv;
  }
  fd_vm_mem_st_2(vm, vaddr, haddr, (ushort)reg_src, is_multi_region);
}
  pc++;
  goto interp_exec;

interp_0x3e:
  reg[dst] = (ulong)(((uint128)reg_dst * (uint128)reg_src) >> 64);
  pc++;
  goto interp_exec;

interp_0x37depr:
  reg[dst] = reg_dst / (ulong)(long)(int)imm;
  pc++;
  goto interp_exec;

interp_0x3cdepr:
  if (__builtin_expect(!!(!(uint)reg_src), 0L))
    goto sigfpe;
  reg[dst] = (ulong)((uint)reg_dst / (uint)reg_src);
  pc++;
  goto interp_exec;

interp_0x3fdepr:
  if (__builtin_expect(!!(!reg_src), 0L))
    goto sigfpe;
  reg[dst] = reg_dst / reg_src;
  pc++;
  goto interp_exec;

interp_0x44:
  reg[dst] = (ulong)((uint)reg_dst | imm);
  pc++;
  goto interp_exec;

interp_0x45:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(!!(reg_dst & (ulong)(long)(int)imm), offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x46:
  reg[dst] = (ulong)((uint)reg_dst / (uint)imm);
  pc++;
  goto interp_exec;

interp_0x47:
  reg[dst] = reg_dst | (ulong)(long)(int)imm;
  pc++;
  goto interp_exec;

interp_0x4c:
  reg[dst] = (ulong)(uint)(reg_dst | reg_src);
  pc++;
  goto interp_exec;

interp_0x4d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(!!(reg_dst & reg_src), offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x4e:
  if (__builtin_expect(!!(!(uint)reg_src), 0L))
    goto sigfpe;
  reg[dst] = (ulong)((uint)reg_dst / (uint)reg_src);
  pc++;
  goto interp_exec;

interp_0x4f:
  reg[dst] = reg_dst | reg_src;
  pc++;
  goto interp_exec;

interp_0x54:
  reg[dst] = (ulong)((uint)reg_dst & imm);
  pc++;
  goto interp_exec;

interp_0x55:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst != (ulong)(long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x56:
  reg[dst] = reg_dst / (ulong)imm;
  pc++;
  goto interp_exec;

interp_0x57:
  reg[dst] = reg_dst & (ulong)(long)(int)imm;
  pc++;
  goto interp_exec;

interp_0x5c:
  reg[dst] = (ulong)(uint)(reg_dst & reg_src);
  pc++;
  goto interp_exec;

interp_0x5d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst != reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x5e:
  if (__builtin_expect(!!(!reg_src), 0L))
    goto sigfpe;
  reg[dst] = reg_dst / reg_src;
  pc++;
  goto interp_exec;

interp_0x5f:
  reg[dst] = reg_dst & reg_src;
  pc++;
  goto interp_exec;

interp_0x64:

  reg[dst] = (ulong)(((uint)reg_dst << ((uint)imm & (31))));
  pc++;
  goto interp_exec;

interp_0x65:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst > (long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x66:
  reg[dst] = (ulong)((uint)reg_dst % (uint)imm);
  pc++;
  goto interp_exec;

interp_0x67:

  reg[dst] = (reg_dst << (imm & (63)));
  pc++;
  goto interp_exec;

interp_0x6c:

  reg[dst] = (ulong)(((uint)reg_dst << (reg_src & (31))));
  pc++;
  goto interp_exec;

interp_0x6d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst > (long)reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x6e:
  if (__builtin_expect(!!(!(uint)reg_src), 0L))
    goto sigfpe;
  reg[dst] = (ulong)((uint)reg_dst % (uint)reg_src);
  pc++;
  goto interp_exec;

interp_0x6f:

  reg[dst] = (reg_dst << (reg_src & (63)));
  pc++;
  goto interp_exec;

interp_0x74:

  reg[dst] = (ulong)(((uint)reg_dst >> (imm & (31))));
  pc++;
  goto interp_exec;

interp_0x75:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst >= (long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x76:
  reg[dst] = reg_dst % (ulong)imm;
  pc++;
  goto interp_exec;

interp_0x77:

  reg[dst] = (reg_dst >> (imm & (63)));
  pc++;
  goto interp_exec;

interp_0x7c:

  reg[dst] = (ulong)(((uint)reg_dst >> ((uint)reg_src & (31))));
  pc++;
  goto interp_exec;

interp_0x7d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst >= (long)reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x7e:
  if (__builtin_expect(!!(!reg_src), 0L))
    goto sigfpe;
  reg[dst] = reg_dst % reg_src;
  pc++;
  goto interp_exec;

interp_0x7f:

  reg[dst] = (reg_dst >> (reg_src & (63)));
  pc++;
  goto interp_exec;

interp_0x84:
  reg[dst] = (ulong)(-(uint)reg_dst);
  pc++;
  goto interp_exec;

interp_0x85:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;

  shadow[frame_cnt].r6 = reg[6];
  shadow[frame_cnt].r7 = reg[7];
  shadow[frame_cnt].r8 = reg[8];
  shadow[frame_cnt].r9 = reg[9];
  shadow[frame_cnt].r10 = reg[10];
  shadow[frame_cnt].pc = pc;
  if (__builtin_expect(!!(++frame_cnt >= frame_max), 0L))
    goto sigstack;
  if (!(sbpf_version >= (1UL)))
    reg[10] += vm->stack_frame_size;
  ;
  pc = (ulong)((long)pc + (long)(int)imm);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x85depr:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  {

    fd_sbpf_syscalls_t const *syscall =
        imm != fd_sbpf_syscalls_key_null()
            ? fd_sbpf_syscalls_query_const(
                  syscalls, (ulong)imm,
                  // # 792 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                  ((void *)0)
                  // # 792 "src/flamenco/vm/fd_vm_interp_core.c"
                  )
            :
            // # 792 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
            ((void *)0)
        // # 792 "src/flamenco/vm/fd_vm_interp_core.c"
        ;
    if (__builtin_expect(!!(!syscall), 0L)) {
      // # 819 "src/flamenco/vm/fd_vm_interp_core.c"
      if (__builtin_expect(!!(imm == 0x71e3cf81U), 0L)) {
        shadow[frame_cnt].r6 = reg[6];
        shadow[frame_cnt].r7 = reg[7];
        shadow[frame_cnt].r8 = reg[8];
        shadow[frame_cnt].r9 = reg[9];
        shadow[frame_cnt].r10 = reg[10];
        shadow[frame_cnt].pc = pc;
        if (__builtin_expect(!!(++frame_cnt >= frame_max), 0L))
          goto sigstack;
        if (!(sbpf_version >= (1UL)))
          reg[10] += vm->stack_frame_size;
        ;
        pc = entry_pc - 1;
      } else {
        ulong target_pc = (ulong)fd_pchash_inverse(imm);
        if (__builtin_expect(!!(target_pc >= text_cnt), 0L)) {
          goto sigillbr;
        }
        if (__builtin_expect(!!(!fd_sbpf_calldests_test(calldests, target_pc)),
                             0L)) {
          goto sigillbr;
        }
        shadow[frame_cnt].r6 = reg[6];
        shadow[frame_cnt].r7 = reg[7];
        shadow[frame_cnt].r8 = reg[8];
        shadow[frame_cnt].r9 = reg[9];
        shadow[frame_cnt].r10 = reg[10];
        shadow[frame_cnt].pc = pc;
        if (__builtin_expect(!!(++frame_cnt >= frame_max), 0L))
          goto sigstack;
        if (!(sbpf_version >= (1UL)))
          reg[10] += vm->stack_frame_size;
        ;
        pc = target_pc - 1;
      }

    } else {

      vm->pc = pc;
      vm->ic = ic;
      vm->cu = cu;
      vm->frame_cnt = frame_cnt;
      if (__builtin_expect(!!(vm->dump_syscall_to_pb), 0L)) {
        fd_dump_vm_syscall_to_protobuf(vm, syscall->name);
      }
      ulong ret[1];
      err = syscall->func(vm, reg[1], reg[2], reg[3], reg[4], reg[5], ret);
      reg[0] = ret[0];
      ulong cu_req = vm->cu;
      cu = fd_ulong_min(cu_req, cu);
      if (__builtin_expect(!!(err), 0L)) {
        if (err == (-24))
          cu = 0UL;
        ((void)0);
        goto sigsyscall;
      };
    }
  }
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x86:
  reg[dst] = (ulong)((uint)reg_dst * imm);
  pc++;
  goto interp_exec;

interp_0x87: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(uint), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);

    if (vm->direct_mapping) {

      uint val = (uint)imm;
      fd_vm_mem_st_try(vm, vaddr, sizeof(uint), (uchar *)&val);
    }

    goto sigsegv;
  }
  fd_vm_mem_st_4(vm, vaddr, haddr, imm, is_multi_region);
}
  pc++;
  goto interp_exec;

interp_0x87depr:
  reg[dst] = -reg_dst;
  pc++;
  goto interp_exec;

interp_0x8c: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_src + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(uint), region_haddr,
                                region_ld_sz, 0, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (1);
    goto sigsegv;
  }
  reg[dst] = fd_vm_mem_ld_4(vm, vaddr, haddr, is_multi_region);
}
  pc++;
  goto interp_exec;

interp_0x8d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  {
    shadow[frame_cnt].r6 = reg[6];
    shadow[frame_cnt].r7 = reg[7];
    shadow[frame_cnt].r8 = reg[8];
    shadow[frame_cnt].r9 = reg[9];
    shadow[frame_cnt].r10 = reg[10];
    shadow[frame_cnt].pc = pc;
    if (__builtin_expect(!!(++frame_cnt >= frame_max), 0L))
      goto sigstack;
    if (!(sbpf_version >= (1UL)))
      reg[10] += vm->stack_frame_size;
    ;
    ulong target_pc = (reg_src - vm->text_off) / 8UL;
    if (__builtin_expect(!!(target_pc >= text_cnt), 0L))
      goto sigtextbr;
    if (__builtin_expect(!!(!fd_sbpf_calldests_test(calldests, target_pc)),
                         0L)) {
      goto sigillbr;
    }
    pc = target_pc - 1;
  }
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x8ddepr:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  {

    shadow[frame_cnt].r6 = reg[6];
    shadow[frame_cnt].r7 = reg[7];
    shadow[frame_cnt].r8 = reg[8];
    shadow[frame_cnt].r9 = reg[9];
    shadow[frame_cnt].r10 = reg[10];
    shadow[frame_cnt].pc = pc;
    if (__builtin_expect(!!(++frame_cnt >= frame_max), 0L))
      goto sigstack;
    if (!(sbpf_version >= (1UL)))
      reg[10] += vm->stack_frame_size;
    ;

    ulong vaddr = (sbpf_version >= (2UL)) ? reg_src : reg[imm & 15U];

    ulong region = vaddr >> 32;

    ulong target_pc = ((vaddr & (0xffffffffUL)) - vm->text_off) / 8UL;
    if (__builtin_expect(!!((region != 1UL) | (target_pc >= text_cnt)), 0L))
      goto sigtextbr;
    pc = target_pc - 1;
  }
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x8e:
  reg[dst] = (ulong)((uint)reg_dst * (uint)reg_src);
  pc++;
  goto interp_exec;

interp_0x8f: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(uint), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);

    if (vm->direct_mapping) {

      uint val = (uint)reg_src;
      fd_vm_mem_st_try(vm, vaddr, sizeof(uint), (uchar *)&val);
    }

    goto sigsegv;
  }
  fd_vm_mem_st_4(vm, vaddr, haddr, (uint)reg_src, is_multi_region);
}
  pc++;
  goto interp_exec;

interp_0x94:
  reg[dst] = (ulong)((uint)reg_dst % imm);
  pc++;
  goto interp_exec;

interp_0x95:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  {

    fd_sbpf_syscalls_t const *syscall = fd_sbpf_syscalls_query_const(
        syscalls, (ulong)imm,
        // # 945 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
        ((void *)0)
        // # 945 "src/flamenco/vm/fd_vm_interp_core.c"
    );
    if (__builtin_expect(!!(!syscall), 0L))
      goto sigillbr;

    vm->pc = pc;
    vm->ic = ic;
    vm->cu = cu;
    vm->frame_cnt = frame_cnt;
    if (__builtin_expect(!!(vm->dump_syscall_to_pb), 0L)) {
      fd_dump_vm_syscall_to_protobuf(vm, syscall->name);
    }
    ulong ret[1];
    err = syscall->func(vm, reg[1], reg[2], reg[3], reg[4], reg[5], ret);
    reg[0] = ret[0];
    ulong cu_req = vm->cu;
    cu = fd_ulong_min(cu_req, cu);
    if (__builtin_expect(!!(err), 0L)) {
      if (err == (-24))
        cu = 0UL;
      ((void)0);
      goto sigsyscall;
    };
  }
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x96:
  reg[dst] = reg_dst * (ulong)(long)(int)imm;
  pc++;
  goto interp_exec;

interp_0x97: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(ulong), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);

    if (vm->direct_mapping) {

      ulong val = (ulong)(long)(int)imm;
      fd_vm_mem_st_try(vm, vaddr, sizeof(ulong), (uchar *)&val);
    }

    goto sigsegv;
  }
  fd_vm_mem_st_8(vm, vaddr, haddr, (ulong)(long)(int)imm, is_multi_region);
}
  pc++;
  goto interp_exec;

interp_0x9c: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_src + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(ulong), region_haddr,
                                region_ld_sz, 0, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (1);
    goto sigsegv;
  }
  reg[dst] = fd_vm_mem_ld_8(vm, vaddr, haddr, is_multi_region);
}
  pc++;
  goto interp_exec;

interp_0x9d:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;

  if (__builtin_expect(!!(!frame_cnt), 0L))
    goto sigexit;
  frame_cnt--;
  reg[6] = shadow[frame_cnt].r6;
  reg[7] = shadow[frame_cnt].r7;
  reg[8] = shadow[frame_cnt].r8;
  reg[9] = shadow[frame_cnt].r9;
  reg[10] = shadow[frame_cnt].r10;
  pc = shadow[frame_cnt].pc;
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0x9e:
  reg[dst] = reg_dst * reg_src;
  pc++;
  goto interp_exec;

interp_0x9f: {
  uchar is_multi_region = 0;
  ulong vaddr = reg_dst + offset;
  ulong haddr = fd_vm_mem_haddr(vm, vaddr, sizeof(ulong), region_haddr,
                                region_st_sz, 1, 0UL, &is_multi_region);
  int sigsegv = !haddr;
  if (__builtin_expect(!!(sigsegv), 0L)) {
    vm->segv_vaddr = vaddr;
    vm->segv_access_type = (2);

    if (vm->direct_mapping) {

      fd_vm_mem_st_try(vm, vaddr, sizeof(ulong), (uchar *)&reg_src);
    }

    goto sigsegv;
  }
  fd_vm_mem_st_8(vm, vaddr, haddr, reg_src, is_multi_region);
}
  pc++;
  goto interp_exec;

interp_0x97depr:
  reg[dst] = reg_dst % (ulong)(long)(int)imm;
  pc++;
  goto interp_exec;

interp_0x9cdepr:
  if (__builtin_expect(!!(!(uint)reg_src), 0L))
    goto sigfpe;
  reg[dst] = (ulong)(((uint)reg_dst % (uint)reg_src));
  pc++;
  goto interp_exec;

interp_0x9fdepr:
  if (__builtin_expect(!!(!reg_src), 0L))
    goto sigfpe;
  reg[dst] = reg_dst % reg_src;
  pc++;
  goto interp_exec;

interp_0xa4:
  reg[dst] = (ulong)((uint)reg_dst ^ imm);
  pc++;
  goto interp_exec;

interp_0xa5:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst < (ulong)(long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0xa7:
  reg[dst] = reg_dst ^ (ulong)(long)(int)imm;
  pc++;
  goto interp_exec;

interp_0xac:
  reg[dst] = (ulong)(uint)(reg_dst ^ reg_src);
  pc++;
  goto interp_exec;

interp_0xad:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst < reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0xaf:
  reg[dst] = reg_dst ^ reg_src;
  pc++;
  goto interp_exec;

interp_0xb4:
  reg[dst] = (ulong)imm;
  pc++;
  goto interp_exec;

interp_0xb5:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst <= (ulong)(long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0xb6:
  reg[dst] = (ulong)(((int128)(long)reg_dst * (int128)(long)(int)imm) >> 64);
  pc++;
  goto interp_exec;

interp_0xb7:
  reg[dst] = (ulong)(long)(int)imm;
  pc++;
  goto interp_exec;

interp_0xbc:
  reg[dst] = (ulong)(long)(int)reg_src;
  pc++;
  goto interp_exec;

interp_0xbcdepr:
  reg[dst] = (ulong)(uint)reg_src;
  pc++;
  goto interp_exec;

interp_0xbd:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if(reg_dst <= reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0xbe:
  reg[dst] = (ulong)(((int128)(long)reg_dst * (int128)(long)reg_src) >> 64);
  pc++;
  goto interp_exec;

interp_0xbf:
  reg[dst] = reg_src;
  pc++;
  goto interp_exec;

interp_0xc4:
  reg[dst] = (ulong)(uint)((int)reg_dst >> imm);
  pc++;
  goto interp_exec;

interp_0xc5:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst < (long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0xc6:
  if (__builtin_expect(!!(((int)reg_dst ==
                           // # 1120 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffff - 1)
                           // # 1120 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((int)imm == -1)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)(uint)((int)reg_dst / (int)imm);
  pc++;
  goto interp_exec;

interp_0xc7:
  reg[dst] = (ulong)((long)reg_dst >> imm);
  pc++;
  goto interp_exec;

interp_0xcc:
  reg[dst] = (ulong)(uint)((int)reg_dst >> (uint)reg_src);
  pc++;
  goto interp_exec;

interp_0xcd:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst < (long)reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0xce:
  if (__builtin_expect(!!(!(int)reg_src), 0L))
    goto sigfpe;
  if (__builtin_expect(!!(((int)reg_dst ==
                           // # 1138 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffff - 1)
                           // # 1138 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((int)reg_src == -1)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)(uint)((int)reg_dst / (int)reg_src);
  pc++;
  goto interp_exec;

interp_0xcf:
  reg[dst] = (ulong)((long)reg_dst >> reg_src);
  pc++;
  goto interp_exec;

interp_0xd4:
  switch (imm) {
  case 16U:
    reg[dst] = (ushort)reg_dst;
    break;
  case 32U:
    reg[dst] = (uint)reg_dst;
    break;
  case 64U:
    break;
  default:
    goto siginv;
  }
  pc++;
  goto interp_exec;

interp_0xd5:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst <= (long)(int)imm, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0xd6:
  if (__builtin_expect(!!(((long)reg_dst ==
                           // # 1162 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffffffffffffL - 1L)
                           // # 1162 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((long)(int)imm == -1L)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)((long)reg_dst / (long)(int)imm);
  pc++;
  goto interp_exec;

interp_0xdc:
  switch (imm) {
  case 16U:
    reg[dst] = (ulong)fd_ushort_bswap((ushort)reg_dst);
    break;
  case 32U:
    reg[dst] = (ulong)fd_uint_bswap((uint)reg_dst);
    break;
  case 64U:
    reg[dst] = fd_ulong_bswap((ulong)reg_dst);
    break;
  default:
    goto siginv;
  }
  pc++;
  goto interp_exec;

interp_0xdd:
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    goto sigcost;
  cu -= ic_correction;
  ic_correction = 0UL;
  pc += fd_ulong_if((long)reg_dst <= (long)reg_src, offset, 0UL);
  pc++;
  pc0 = pc;
  goto interp_exec;

interp_0xde:
  if (__builtin_expect(!!(!reg_src), 0L))
    goto sigfpe;
  if (__builtin_expect(!!(((long)reg_dst ==
                           // # 1181 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffffffffffffL - 1L)
                           // # 1181 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((long)reg_src == -1L)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)((long)reg_dst / (long)reg_src);
  pc++;
  goto interp_exec;

interp_0xe6:
  if (__builtin_expect(!!(((int)reg_dst ==
                           // # 1188 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffff - 1)
                           // # 1188 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((int)imm == -1)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)(uint)((int)reg_dst % (int)imm);
  pc++;
  goto interp_exec;

interp_0xee:
  if (__builtin_expect(!!(!(int)reg_src), 0L))
    goto sigfpe;
  if (__builtin_expect(!!(((int)reg_dst ==
                           // # 1194 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffff - 1)
                           // # 1194 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((int)reg_src == -1)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)(uint)((int)reg_dst % (int)reg_src);
  pc++;
  goto interp_exec;

interp_0xf6:
  if (__builtin_expect(!!(((long)reg_dst ==
                           // # 1201 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffffffffffffL - 1L)
                           // # 1201 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((long)(int)imm == -1L)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)((long)reg_dst % (long)(int)imm);
  pc++;
  goto interp_exec;

interp_0xf7:
  reg[dst] = reg_dst | (((ulong)imm) << 32);
  pc++;
  goto interp_exec;

interp_0xfe:
  if (__builtin_expect(!!(!reg_src), 0L))
    goto sigfpe;
  if (__builtin_expect(!!(((long)reg_dst ==
                           // # 1211 "src/flamenco/vm/fd_vm_interp_core.c" 3 4
                           (-0x7fffffffffffffffL - 1L)
                           // # 1211 "src/flamenco/vm/fd_vm_interp_core.c"
                           ) &
                          ((long)reg_src == -1L)),
                       0L))
    goto sigfpeof;
  reg[dst] = (ulong)((long)reg_dst % (long)reg_src);
  pc++;
  goto interp_exec;
// # 1246 "src/flamenco/vm/fd_vm_interp_core.c"
sigtext:
  err = (-7);
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    err = (-9);
  cu -= fd_ulong_min(ic_correction, cu);
  goto interp_halt;
sigtextbr:
  err = (-8);
  goto interp_halt;
sigstack:
  err = (-3);
  goto interp_halt;
sigill:
  err = (-16);
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    err = (-9);
  cu -= fd_ulong_min(ic_correction, cu);
  goto interp_halt;
sigillbr:
  err = (-16);
  goto interp_halt;
siginv:
  err = (-15);
  goto interp_halt;
sigsegv:
  err = fd_vm_generate_access_violation(vm->segv_vaddr, vm->sbpf_version);
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    err = (-9);
  cu -= fd_ulong_min(ic_correction, cu);
  goto interp_halt;
sigcost:
  err = (-9);
  cu = 0UL;
  goto interp_halt;
sigsyscall:
  err = (-20);
  goto interp_halt;
sigfpe:
  err = (-5);
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    err = (-9);
  cu -= fd_ulong_min(ic_correction, cu);
  goto interp_halt;
sigfpeof:
  err = (-6);
  ic_correction = pc - pc0 + 1UL - ic_correction;
  ic += ic_correction;
  if (__builtin_expect(!!(ic_correction > cu), 0L))
    err = (-9);
  cu -= fd_ulong_min(ic_correction, cu);
  goto interp_halt;
sigexit:
  goto interp_halt;

interp_halt:

  vm->pc = pc;
  vm->ic = ic;
  vm->cu = cu;
  vm->frame_cnt = frame_cnt;
// # 1285 "src/flamenco/vm/fd_vm_interp_core.c"
#pragma GCC diagnostic pop
  // # 67 "src/flamenco/vm/fd_vm_interp.c" 2

  return err;
}
