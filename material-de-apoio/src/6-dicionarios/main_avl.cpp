import avl;
import std;

int main() { 
    AVL avl;
    avl.cria();
    avl.upsert('M', 1.0);
    avl.upsert('D', 2.0);
    avl.upsert('B', 3.0);
    std::println("rotaciona após B:");
    imprime_vertical_dict(avl.raiz);

    avl.upsert('F', 4.0);
    avl.upsert('E', 5.0);
    std::println("rotaciona após E:");
    imprime_vertical_dict(avl.raiz);

    avl.upsert('L', 6.0);
    std::println("rotaciona após L:");
    imprime_vertical_dict(avl.raiz);

    avl.upsert('O', 7.0);
    avl.upsert('N', 8.0);
    avl.upsert('S', 9.0);

    std::println("final:");
    imprime_vertical_dict(avl.raiz);

    avl.libera();

    AVL avl2;
    avl2.cria();
    avl2.upsert('C', 1.0);
    avl2.upsert('E', 2.0);
    avl2.upsert('D', 3.0);
    std::println("rotacao dupla após D:");
    imprime_vertical_dict(avl2.raiz);

    avl2.libera();

    return 0; 
}
