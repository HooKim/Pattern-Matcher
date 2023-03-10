#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ds.h"

//ADT TEXTLIST

// data structure needs to be first created beforehand
// we will take advantage of dummy node
// root -> [dummy] -> [tok0] -> [tok1] -> ... -> NULL
void tlInit(Tlist *tl){
  tl->root = (Token *)malloc(sizeof (Token));
  tokInit(tl->root);
  tl->tot_line = 0;
  tl->tot_tok = 0;
}

void tlAdd(Tlist *tl, Token *tok){
  Token *cur_tok = tl->root;
  if((tl->tot_tok)++ == 0){
    cur_tok->next = tok;
    return;
  }

  for(int i = 0; i < tl->tot_tok - 1; i++ ){
    cur_tok = cur_tok->next;
  }

  cur_tok->next = tok;
  return;
}

// zero-base idx & [begin, end] inclusive
// this funciton is for detaching tokens from token list with its reference valid
Token * tlSlice(Tlist *tl, int begin, int end){
  if(begin > end || tl->tot_tok == 0){
    return (Token *) NULL;
  }

  int i;
  Token *prev_cur, *cur_tok, *beg_tok, *end_tok;
  prev_cur = tl->root;
  cur_tok = prev_cur->next;

  for(i = 0; i < begin; i++){
    prev_cur = cur_tok;
    cur_tok = cur_tok->next;
  }
  // if(i == 1) prev_cur = prev_cur->next;

  beg_tok = cur_tok;
  for(i = begin; i < end; i++){
    cur_tok = cur_tok->next;
  }
  end_tok = cur_tok;

  prev_cur->next = end_tok->next;
  end_tok->next = NULL;

  tl->tot_tok -= end - begin + 1;

  return beg_tok;
}

Token *tlHead(Tlist * tl){
  return tl->root->next;
}

void printTlist(Tlist *tl){
  Token * cur;
  cur =  tl->root->next;
  int idx = 0;
  while(cur){
    printf("[%d]|%s|-%d-> ", idx++ ,cur->data, cur->line_no);
    cur = cur->next;
  }

  printf("NULL\n");
}

// ADT TOKEN
void tokInit(Token *tok){
  tok->col_no = 0;
  tok->data = NULL;
  tok->line_no = 0;
  tok->next = NULL;
}

void tokSet(Token *tok, char* buf, int line_no, int col_no){
  int length;
  length = strlen(buf);
  tok->data = (char *) malloc(sizeof(char) * (length + 1));
  tok->line_no = line_no;
  tok->col_no = col_no;
  strcpy(tok->data, buf);
}

int tokLen(Token *tok){
  int length = 0;
  Token *cur = tok;
  while(cur){
    length++;
    cur = cur->next;
  }
  return length; 
}

// ADT MATCHED
void mInit(Matched * head){
  head->A = NULL;
  head->B = NULL;
  head->next = NULL;
}
void mPair(Matched * head, Token *A, Token *B){
  Matched * cur;
  cur = head;
  while(cur->next){
    cur = cur->next;
  }
  cur->next = (Matched *)malloc(sizeof(Matched));
  mInit(cur->next);
  cur = cur->next;
  cur->A = A;
  cur->B = B;
}

void printMatched(Matched * head){
  int idx, ln;
  Matched * cur;
  Token * cur_tok;
  cur = head->next;
  idx = 1;

  printf("-------------Match----------------\n");
  while(cur){
    printf("%d match\n", idx++);
    cur_tok = cur->A;
    printf("  - A : \n");
    while(cur_tok){
      ln = cur_tok->line_no;
      printf("    #%d", ln);
      while(cur_tok && ln == cur_tok->line_no){
        printf("[%s, (%d, %d)]", cur_tok->data, cur_tok->line_no, cur_tok->col_no);
        cur_tok = cur_tok->next;
      }
      printf("\n");
    }
    printf("\n");

    cur_tok = cur->B;
    printf("  - B : \n");
    while(cur_tok){
      ln = cur_tok->line_no;
      printf("    #%d", ln);
      while(cur_tok && ln == cur_tok->line_no){
        printf("[%s, (%d, %d)]", cur_tok->data, cur_tok->line_no, cur_tok->col_no);
        cur_tok = cur_tok->next;
      }
      printf("\n");
    }
    printf("\n");

    cur = cur->next;
  }
}