/* 
 * ppu.c
 * by Max Willsey
 * PPU emulation for the NES
 */

#include "nes.h"

void ctrl_wcb (nes* n, byte b) {
  n->p->ctrl = b; 
}  
void mask_wcb (nes* n, byte b) {
  n->p->mask = b; 
} 

void oam_addr_cb (nes* n, byte b) {
  /* not supported right now */
  if  (b != 0x00)
    printf("OAMADDR is not supported right now\n");
  n->p->oam_addr = b; 
}  
void oam_data_cb (nes* n, byte b) {
  /* not supported right now */
  printf("OAMDATA is not implemented\n");
  n->p->oam_addr++;
  n->p->oam_data = b; 
}  
void scroll_cb (nes* n, byte b) {
  /* addr is written byte by byte, lo then hi */
  n->p->scroll = (n->p->scroll << 8) | b; 
}  
void addr_cb (nes* n, byte b) {
  /* addr is written byte by byte, lo then hi */
  n->p->addr = (n->p->addr << 8) | b; 
}  
void data_cb (nes* n, byte b) {
  n->p->data = b; 
}  

void ppu_init (nes *n) {
  ppu *p = n->p;
  p->mem = malloc(sizeof(memory));
  mem_init(p->mem, 0x4000, n);

  /* install callbacks in CPU address space */
  n->c->mem->write_cbs[0x2000] = &ctrl_cb;
  n->c->mem->write_cbs[0x2001] = &mask_cb;
  n->c->mem->write_cbs[0x2003] = &oam_addr_cb;
  n->c->mem->write_cbs[0x2004] = &oam_data_cb;
  n->c->mem->write_cbs[0x2005] = &scroll_cb;
  n->c->mem->write_cbs[0x2006] = &addr_cb;
  n->c->mem->write_cbs[0x2007] = &data_cb;
}

void ppu_destroy (nes *n) {
  free(n->p->mem);
}

















