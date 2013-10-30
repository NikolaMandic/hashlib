union{
  float f;
  int i;
}u;
int hash(int key){
  u.i=key;
  u.i=u.i&0x3f7fffff;
  u.i=u.i|0x3f000000;
  
  return u.f*100;
}
int main(){
  int p=5;
  printf("%p %d\n",&p,hash((int)&p));

}
