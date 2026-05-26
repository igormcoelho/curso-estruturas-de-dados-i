#ifndef SACOTAD_HPP
#define SACOTAD_HPP

// Prof. Igor Machado Coelho
// Copyleft 2021 - MIT License

template <typename Agregado>
concept
#if __cplusplus <= 201703L // after c++20, not required 'bool'
    bool
#endif
        IteradorTAD = requires(Agregado a)
{
   // requer operação 'terminou' (retorna booleano)
   {a.terminou()};
   // requer operação 'atual' (retorna elemento)
   {a.atual()};
   // requer operação 'proximo'
   {a.proximo()};
};

template <typename Agregado>
concept
#if __cplusplus <= 201703L // after c++20, not required 'bool'
    bool
#endif
        SacoTAD = requires(Agregado a,
                           typename Agregado::Tipo t,
                           typename Agregado::ItTipo it)
{
   // requer operação 'adiciona' sobre tipo 't'
   {a.adiciona(t)};
   // requer operação 'itera' (retorna 'it')
   {a.itera()};
   // requer operação 'busca' sobre tipo 't' (retorna 'it')
   {a.busca(t)};
   // requer operação 'remove'
   {a.remove(it)};
};

#endif /* SACOTAD_HPP */