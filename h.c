union{
  float f;
  int i;
}u;
#define L 100
struct Dict{
 void * val;
}dict[L];
int hash(int key,int length){
  u.i=key;
  u.i=u.i&0x3f7fffff;
  u.i=u.i|0x3f000000;
  
  return u.f*length;
}
int dict_store(struct Dict *d,int(*h)(int,int),int key,void * val,int len){
   d[h(key,len)].val=val;
}
int main(){
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
