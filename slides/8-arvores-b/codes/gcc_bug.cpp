struct NoEnc {
   NoEnc* esq; 
   NoEnc* dir;  
};

template <typename X>
X* minimo(X* const no) 
//auto* minimo(NoEnc* const no) 
pre(no)
post(out : !out->esq) 
{
  auto* atual = no;
  while(atual->esq) atual = atual->esq;
  return atual;
};

int main() { 
    auto* no = new NoEnc{.esq=0, .dir=0};
    auto* no2 = minimo(no);
    return 0;
}