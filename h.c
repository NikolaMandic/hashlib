#include <hashlib.h>

int hash(int key,int length){
  u.i=key;
  u.i=u.i&0x3f7fffff;
  u.i=u.i|0x3f000000;
  return u.f*length;
}
int dictm_store(DictM *d,int(*h)(int,int),int key,void * val,int len){
  int k = h(key,len);
  d[k].val=val;
  d[k].key=key;
}
int dict_store(Dict *d,int(*h)(int,int),int key,void * val,int len){
   d[h(key,len)].val=val;
}

int dict_storell(struct DictMLL *d,int(*h)(int,int),int key,void * val,int len){
  int k = h(key,len);
  DictMLL * el= d+k;
  if(el->key==0){
    el->val=val;
    el->key=key;
  }else{
    ll *v=malloc(sizeof(struct ll));
    v->key=key;
    v->val=val;
    v->next=el->next;
    el->val=v;
    el->next=v;
    //d[k].val=
  }
}
void * dict_getll(struct DictMLL *d,int(*h)(int,int),int key,int len){
  int k = h(key,len);
  DictMLL * el= d+k;
  if(el->key==0) return 0;

  if(el->key==key){
    return el->val;
  }else{
    ll *v = el->next;
   
    while(v && v->key!=key){
      v=v->next;
    }
    if (v) return v->val;
  }
}
void d(){
  int p=5;
  int i=0;
  printf("%p %d\n",&p,hash((int)&p,L));
  char * st="charStr";
  dict_store(dict,hash,(int)&st,st,L);
  while(i<100){
    printf("%d = %p\n",i,dict[i].val);
    i++;
  }
}
void printLL(ll * l){
  ll *n = l;
  printf("-%p",n->val);
  while(n=n->next){
    printf("-%p",n->val);
  }
  printf("\n");
}
/*
int main(){
  DictMLL d[100];
  int key;
  void * val=&key;
  int i=0;
  memset(d,0,sizeof(DictMLL)*100);
  dict_storell(d,hash,key,val,100);

  dict_storell(d,hash,key|0x80000000,val+1,100);

  void * v1 = dict_getll(d,hash,key|0x80000000,100);
  void * v2 = dict_getll(d,hash,key,100);
  printf("key=%p|val=%p\nkey=%p|val=%p\n",key|0x80000000,v1,key,v2); 
  while(i<100){
    ll * l;
    printf("\n");
    printf("%d = %p",i,d[i].val);
    if(l=d[i].next){
      printLL(l); 
    }
    i++;
  }
  printf("\n");
}*/
