module;
export module saco_tad;
export import std;

// Prof. Igor Machado Coelho
// Copyleft 2021-2026 - MIT License

export template <typename Agregado>
concept IteradorTAD = requires(Agregado a) {
  // requer operação 'terminou' (retorna booleano)
  { a.terminou() } -> std::same_as<bool>;
  // requer operação 'atual' (retorna elemento)
  { a.atual() } -> std::same_as<typename Agregado::Tipo>;
  // requer operação 'proximo'
  { a.proximo() } -> std::same_as<void>;
};

export template <typename S>
concept SacoTAD = requires(S a, typename S::Tipo t, typename S::ItTipo it) {
  // requer operação 'adiciona' sobre tipo 't'
  { a.adiciona(t) } -> std::same_as<void>;
  // requer operação 'itera' (retorna 'it')
  { a.itera() } -> std::same_as<typename S::ItTipo>;
  // requer operação 'busca' sobre tipo 't' (retorna 'it')
  { a.busca(t) } -> std::same_as<typename S::ItTipo>;
  // requer operação 'remove'
  { a.remove(it) } -> std::same_as<void>;
};
