# Projecto 2 - IAED 2022/2023

## Enunciado

O enunciado do projecto está disponível em [enunciado.md](enunciado.md). 

## Data de entrega: 14 de abril de 2023, às 19h59

Informações detalhadas sobre o processo de submissão estão disponíveis em [informacoes.md](informacoes.md).



# Evaluation

2023-04-11T15:23:19

## Test 1: [+ Accepted+].
## Test 2: [+ Accepted+].
## Test 3: [+ Accepted+].
## Test 4: [+ Accepted+].
## Test 5: [+ Accepted+].
## Test 6: [+ Accepted+].
## Test 7: [+ Accepted+].
## Test 8: [+ Accepted+].
## Test 9: [+ Accepted+].
## Test 10: [+ Accepted+].
## Test 11: [+ Accepted+].
## Test 12: [+ Accepted+].
## Test 13: [+ Accepted+].
## Test 14: [+ Accepted+].
## Test 15: [+ Accepted+].
## Test 16: [+ Accepted+].
## Test 17: [+ Accepted+].
## Test 18: [+ Accepted+].
## Test 19: [+ Accepted+].
## Test 20: [+ Accepted+].
## Test 21: [+ Accepted+].
## Test 22: [+ Accepted+].
## Test 23: [+ Accepted+].
## Test 24: [+ Accepted+].
## Test 25: [+ Accepted+].
## Test 26: [+ Accepted+].
## Test 27: [+ Accepted+].
## Test 28: [+ Accepted+].
## Test 29: [+ Accepted+].
## Test 30: [+ Accepted+].
## Test 31: [+ Accepted+].
## Test 32: [+ Accepted+].


## Number of passed tests: 32/32


## Valgrind Output:


```
==17502== Memcheck, a memory error detector
==17502== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==17502== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
==17502== Command: ./proj.out
==17502== 
ENTERING ELIMINA PARAGEM
exited elimina_paragem normally

ENTERING ELIMINA PARAGEM
==17502== Invalid read of size 4
==17502==    at 0x10B786: eliminaLigacao (project2.c:751)
==17502==    by 0x10B786: eliminaLigacao (project2.c:737)
==17502==    by 0x10B786: eliminaParagem (project2.c:904)
==17502==    by 0x109286: main (project2.c:1064)
==17502==  Address 0x4b9aaa0 is 0 bytes inside a block of size 40 free'd
==17502==    at 0x48369AB: free (vg_replace_malloc.c:530)
==17502==    by 0x10B785: eliminaLigacao (project2.c:750)
==17502==    by 0x10B785: eliminaLigacao (project2.c:737)
==17502==    by 0x10B785: eliminaParagem (project2.c:904)
==17502==    by 0x109286: main (project2.c:1064)
==17502==  Block was alloc'd at
==17502==    at 0x483577F: malloc (vg_replace_malloc.c:299)
==17502==    by 0x10AA5F: criaLigacao (project2.c:533)
==17502==    by 0x10AA5F: adicionaLigacao (project2.c:614)
==17502==    by 0x10AE35: ligacoes (project2.c:682)
==17502==    by 0x109266: main (project2.c:1049)
==17502== 
==17502== Invalid read of size 8
==17502==    at 0x10B788: eliminaLigacao (project2.c:751)
==17502==    by 0x10B788: eliminaLigacao (project2.c:737)
==17502==    by 0x10B788: eliminaParagem (project2.c:904)
==17502==    by 0x109286: main (project2.c:1064)
==17502==  Address 0x4b9aac0 is 32 bytes inside a block of size 40 free'd
==17502==    at 0x48369AB: free (vg_replace_malloc.c:530)
==17502==    by 0x10B785: eliminaLigacao (project2.c:750)
==17502==    by 0x10B785: eliminaLigacao (project2.c:737)
==17502==    by 0x10B785: eliminaParagem (project2.c:904)
==17502==    by 0x109286: main (project2.c:1064)
==17502==  Block was alloc'd at
==17502==    at 0x483577F: malloc (vg_replace_malloc.c:299)
==17502==    by 0x10AA5F: criaLigacao (project2.c:533)
==17502==    by 0x10AA5F: adicionaLigacao (project2.c:614)
==17502==    by 0x10AE35: ligacoes (project2.c:682)
==17502==    by 0x109266: main (project2.c:1049)
==17502== 
==17502== Invalid read of size 4
==17502==    at 0x10B5AB: eliminaParagem (project2.c:898)
==17502==    by 0x109286: main (project2.c:1064)
==17502==  Address 0x4b9aaa4 is 4 bytes inside a block of size 40 free'd
==17502==    at 0x48369AB: free (vg_replace_malloc.c:530)
==17502==    by 0x10B785: eliminaLigacao (project2.c:750)
==17502==    by 0x10B785: eliminaLigacao (project2.c:737)
==17502==    by 0x10B785: eliminaParagem (project2.c:904)
==17502==    by 0x109286: main (project2.c:1064)
==17502==  Block was alloc'd at
==17502==    at 0x483577F: malloc (vg_replace_malloc.c:299)
==17502==    by 0x10AA5F: criaLigacao (project2.c:533)
==17502==    by 0x10AA5F: adicionaLigacao (project2.c:614)
==17502==    by 0x10AE35: ligacoes (project2.c:682)
==17502==    by 0x109266: main (project2.c:1049)
==17502== 
==17502== Invalid read of size 8
==17502==    at 0x10B6B8: eliminaParagem (project2.c:900)
==17502==    by 0x109286: main (project2.c:1064)
==17502==  Address 0x4b9aaa8 is 8 bytes inside a block of size 40 free'd
==17502==    at 0x48369AB: free (vg_replace_malloc.c:530)
==17502==    by 0x10B785: eliminaLigacao (project2.c:750)
==17502==    by 0x10B785: eliminaLigacao (project2.c:737)
==17502==    by 0x10B785: eliminaParagem (project2.c:904)
==17502==    by 0x109286: main (project2.c:1064)
==17502==  Block was alloc'd at
==17502==    at 0x483577F: malloc (vg_replace_malloc.c:299)
==17502==    by 0x10AA5F: criaLigacao (project2.c:533)
==17502==    by 0x10AA5F: adicionaLigacao (project2.c:614)
==17502==    by 0x10AE35: ligacoes (project2.c:682)
==17502==    by 0x109266: main (project2.c:1049)
==17502== 
==17502== Invalid read of size 8
==17502==    at 0x10B6BD: eliminaParagem (project2.c:900)
==17502==    by 0x109286: main (project2.c:1064)
==17502==  Address 0x4b9aab0 is 16 bytes inside a block of size 40 free'd
==17502==    at 0x48369AB: free (vg_replace_malloc.c:530)
==17502==    by 0x10B785: eliminaLigacao (project2.c:750)
==17502==    by 0x10B785: eliminaLigacao (project2.c:737)
==17502==    by 0x10B785: eliminaParagem (project2.c:904)
==17502==    by 0x109286: main (project2.c:1064)
==17502==  Block was alloc'd at
==17502==    at 0x483577F: malloc (vg_replace_malloc.c:299)
==17502==    by 0x10AA5F: criaLigacao (project2.c:533)
==17502==    by 0x10AA5F: adicionaLigacao (project2.c:614)
==17502==    by 0x10AE35: ligacoes (project2.c:682)
==17502==    by 0x109266: main (project2.c:1049)
==17502== 
==17502== Invalid read of size 8
==17502==    at 0x10B771: eliminaLigacao (project2.c:747)
==17502==    by 0x10B771: eliminaLigacao (project2.c:737)
==17502==    by 0x10B771: eliminaParagem (project2.c:904)
==17502==    by 0x109286: main (project2.c:1064)
==17502==  Address 0x4b9aab8 is 24 bytes inside a block of size 40 free'd
==17502==    at 0x48369AB: free (vg_replace_malloc.c:530)
==17502==    by 0x10B785: eliminaLigacao (project2.c:750)
==17502==    by 0x10B785: eliminaLigacao (project2.c:737)
==17502==    by 0x10B785: eliminaParagem (project2.c:904)
==17502==    by 0x109286: main (project2.c:1064)
==17502==  Block was alloc'd at
==17502==    at 0x483577F: malloc (vg_replace_malloc.c:299)
==17502==    by 0x10AA5F: criaLigacao (project2.c:533)
==17502==    by 0x10AA5F: adicionaLigacao (project2.c:614)
==17502==    by 0x10AE35: ligacoes (project2.c:682)
==17502==    by 0x109266: main (project2.c:1049)
==17502== 
==17502== Invalid free() / delete / delete[] / realloc()
==17502==    at 0x48369AB: free (vg_replace_malloc.c:530)
==17502==    by 0x10B785: eliminaLigacao (project2.c:750)
==17502==    by 0x10B785: eliminaLigacao (project2.c:737)
==17502==    by 0x10B785: eliminaParagem (project2.c:904)
==17502==    by 0x109286: main (project2.c:1064)
==17502==  Address 0x4b9aaa0 is 0 bytes inside a block of size 40 free'd
==17502==    at 0x48369AB: free (vg_replace_malloc.c:530)
==17502==    by 0x10B785: eliminaLigacao (project2.c:750)
==17502==    by 0x10B785: eliminaLigacao (project2.c:737)
==17502==    by 0x10B785: eliminaParagem (project2.c:904)
==17502==    by 0x109286: main (project2.c:1064)
==17502==  Block was alloc'd at
==17502==    at 0x483577F: malloc (vg_replace_malloc.c:299)
==17502==    by 0x10AA5F: criaLigacao (project2.c:533)
==17502==    by 0x10AA5F: adicionaLigacao (project2.c:614)
==17502==    by 0x10AE35: ligacoes (project2.c:682)
==17502==    by 0x109266: main (project2.c:1049)
==17502== 
==17502== 
==17502== More than 10000000 total errors detected.  I'm not reporting any more.
==17502== Final error counts will be inaccurate.  Go fix your program!
==17502== Rerun with --error-limit=no to disable this cutoff.  Note
==17502== that errors may occur in your program without prior warning from
==17502== Valgrind, because errors are no longer being displayed.
==17502== 

```


Your code will not be reevaluated if you submit before 2023-04-11 15:33:19 @ Lisbon, Portugal. You need to wait 10 minute(s).

