/*
 * Redistribution and use in source and binary forms, with
 * or without modification, are permitted provided that the
 * following conditions are met:
 *
 * 1. Redistributions of source code must retain this list
 *    of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce this
 *    list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
#ifndef THANM_H_
#define THANM_H_

#include <config.h>
#include <inttypes.h>
#include "list.h"

extern unsigned int option_force;

typedef struct {
#ifdef PACK_PRAGMA
#pragma pack(push,1)
#endif
    uint32_t id;
    float x, y, w, h;
#ifdef PACK_PRAGMA
#pragma pack(pop)
#endif
} PACK_ATTRIBUTE sprite_t;

typedef struct {
#ifdef PACK_PRAGMA
#pragma pack(push,1)
#endif
    uint16_t time;
    uint8_t type;
    /* XXX: data length. */
    uint8_t length;
#ifdef PACK_PRAGMA
#pragma pack(pop)
#endif
    unsigned char data[];
} PACK_ATTRIBUTE anm_instr0_t;

typedef struct {
#ifdef PACK_PRAGMA
#pragma pack(push,1)
#endif
    uint16_t type;
    uint16_t length;
    uint16_t time;
    /* TODO: Implement this, it works similarly to that one in ECL files. */
    uint16_t param_mask;
#ifdef PACK_PRAGMA
#pragma pack(pop)
#endif
    unsigned char data[];
} PACK_ATTRIBUTE anm_instr_t;

/* TODO: Rename this struct to _header_t something. */
typedef struct {
#ifdef PACK_PRAGMA
#pragma pack(push,1)
#endif
    int32_t id;
    uint32_t offset;
#ifdef PACK_PRAGMA
#pragma pack(pop)
#endif
} PACK_ATTRIBUTE anm_offset_t;

typedef struct {
    anm_offset_t* offset;
    list_t instrs;
} anm_script_t;

typedef struct {
    uint16_t type;
    const char* format;
} opcode_fmt_t;

typedef struct {
#ifdef PACK_PRAGMA
#pragma pack(push,1)
#endif
    uint32_t sprites;
    uint32_t scripts;
    uint32_t zero1;
    uint32_t w, h;
    uint32_t format;
    uint32_t zero2; /* XXX: A few are 0xff000000. */
    uint32_t nameoffset;
    /* XXX: X is unused here. */
    /* XXX: Y stores the secondary name offset for TH06.
     *      There is no secondary name when it is zero. */
    uint32_t x, y;
    /* 0: TH06
     * 2: TH07
     * 3: TH08, TH09
     * 4: TH95, TH10
     * 7: TH11, TH12, TH125 */
    uint32_t version;
    /* 0  - Random things, everything in TH06. */
    /* 1  - data/ascii/loading.png for TH08 and TH09. */
    /* 10 - Mostly sprites? */
    /* 11 - Used mainly for backgrounds and ascii.png. */
    uint32_t unknown1;
    uint32_t thtxoffset;
    uint16_t hasdata;
    uint16_t unknown2;
    uint32_t nextoffset;
    uint32_t zero3;
#ifdef PACK_PRAGMA
#pragma pack(pop)
#endif
} PACK_ATTRIBUTE anm_header_t;

typedef struct {
#ifdef PACK_PRAGMA
#pragma pack(push,1)
#endif
    uint32_t version;
    uint16_t sprites;
    uint16_t scripts;
    uint16_t zero1;
    uint16_t w, h;
    uint16_t format;
    uint32_t nameoffset;
    uint16_t x, y;
    uint32_t unknown1;
    uint32_t thtxoffset;
    uint16_t hasdata;
    uint16_t unknown2;
    uint32_t nextoffset;
    uint32_t zero2[6];
#ifdef PACK_PRAGMA
#pragma pack(pop)
#endif
} PACK_ATTRIBUTE anm_header11_t;

typedef struct {
#ifdef PACK_PRAGMA
#pragma pack(push,1)
#endif
    char magic[4];
    uint16_t zero;
    uint16_t format;
    /* These may be different from the parent entry. */
    uint16_t w, h;
    uint32_t size;
#ifdef PACK_PRAGMA
#pragma pack(pop)
#endif
    unsigned char data[];
} PACK_ATTRIBUTE thtx_header_t;

typedef struct {
    anm_header_t* header;
    thtx_header_t* thtx;

    char* name;
    char* name2;

    /* List of sprite_t*. */
    list_t sprites;
    /* List of anm_script_t*. */
    list_t scripts;

    unsigned char* data;
} anm_entry_t;

typedef struct {
    unsigned char* map;
    long map_size;

    /* List of const char*. */
    list_t names;
    /* List of anm_entry_t*. */
    list_t entries;
} anm_archive_t;

#endif
