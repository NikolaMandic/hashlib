union{
  float f;
  int i;
}u;
#define L 100
struct Dict{
 void * val;
}dict[L];

typedef struct DictM{
 int key;
 void * val;
}DictM;

typedef struct DictMLL{
 int key;
 void * val;
 void * next;
}DictMLL;
int hash(int key,int length){
  u.i=key;
  u.i=u.i&0x3f7fffff;
  u.i=u.i|0x3f000000;
  return u.f*length;
}

int dictm_store(struct DictM *d,int(*h)(int,int),int key,void * val,int len){
  int k = h(key,len);
  d[k].val=val;
  d[k].key=key;
}
int dict_store(struct Dict *d,int(*h)(int,int),int key,void * val,int len){
   d[h(key,len)].val=val;
}

typedef struct ll ll;
typedef struct ll{
  void *val;
  ll * next;
}ll;
int dict_storell(struct DictMLL *d,int(*h)(int,int),int key,void * val,int len){
  int k = h(key,len);
  DictMLL * el= d+k;
  if(el->key==0){
    el->val=val;
    el->key=key;
  }else{
    ll *v=malloc(sizeof(struct ll));
    v->val=val;
    v->next=el->next;
    el->val=v;
    el->next=v;
    //d[k].val=
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
int main(){
  /*
  ll *l;
  l->val=4;
  printf("%p\n",l->val);
  */
  DictMLL d[100];
  int key;
  void * val=&key;
  int i=0;
  memset(d,0,sizeof(DictMLL)*100);
  dict_storell(d,hash,key,val,100);

  dict_storell(d,hash,key,val+1,100);
  
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
}
