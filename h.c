#include "hashlib.h"

int hash(int key,int length){
  u.i=key;
  u.i=u.i&0x3f7fffff;
  u.i=u.i|0x3f000000;
  return u.f*length;
}
int h3(int key,int length){
  return key%length ;
}
int refHash(int key,int length){
  return key%length;
}
int dictm_store(DictM *d,int(*h)(int,int),int key,void * val,int len){
  int k = h(key,len);
  d[k].val=val;
  d[k].key=key;
}
int dict_store(Dict *d,int(*h)(int,int),int key,void * val,int len){
   d[h(key,len)].val=val;
}
int dict_storeN(Dict *d,int(*h)(int,int),int key,void * val,int len){
  int k=h(key,len);
  while(d[k].val!=0 ){
    k =(k+1)%len;
  }
  d[k].val=val;
}
int dict_get(Dict *d,int(*h)(int,int),int key,int len){
   return d[h(key,len)].val;
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
  /*
  int p=5;
  int i=0;
  printf("%p %d\n",&p,hash((int)&p,L));
  char * st="charStr";
  dict_store(dict,hash,(int)&st,st,L);
  while(i<100){
    printf("%d = %p\n",i,dict[i].val);
    i++;
  }
  */
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
  int collisions[15];
  int*  m[3] ={hash,refHash,h3} ;

  memset(collisions,0,sizeof(int)*15);
  int lengths[]={10,100,1000,10000,100000,1000000};

  //int lengths[]={10,100};
  int llen = 4;
  Dict * dict;
  printf("before loop\n");

  int fcounter=0;
  while(fcounter<3){
    int (*h)(int,int)=0;
    void* v = m[fcounter];

    int i=0;
    h=v;

    while (i<llen){
      int j=0;
      srand(10);
      dict = (Dict*) malloc(lengths[i]*sizeof(Dict));
      memset(dict, 0, lengths[i]*sizeof(Dict));
      
      printf("before loop\n");
      while(j<lengths[i]){
        int r = malloc(50);
        if(dict_get(dict,v,r,lengths[i])==0){

          dict_store(dict,v,r,&r,lengths[i]);
        }else{

          dict_storeN(dict,v,r,&r,lengths[i]);
          collisions[fcounter*llen+i]+=1;
        }
        j++;
      }
      free(dict);
      i++;
    }
    fcounter++;
  }
  {
    int i=0;
    for(i=0;i<3*llen;i++){

      printf("function %d num of el = collisions %d = %d\n",i/llen,lengths[i%llen],collisions[i]);

    }
  }
  /*
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
  */
  printf("\n");
}
