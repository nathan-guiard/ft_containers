# Dependances importantes

- insert (`enable_if`)
- operateurs de comparaisons des iterateurs
- operateurs `-` et `+` des iterateurs

## A faire compiler

- [ ] assign
  - probleme de type (enable if)
- [ ] bidirect_it
  - dependance `insert`
- [ ] erase
  - pas d'operateur `-` entre `it` et `const it`
- [ ] insert
  - erreur de linkage
- [ ] insert2
  - erreur de linkage
- [ ] ite
  - manque operateur `int - it` (surement faisable avec enable if)
- [ ] relational_ope
  - linkage -> pas code `resize`
- [ ] rite2
  - manque des operateurs
- [ ] rite_arrow
  - construction dun `rev_it` a partir d'un `const_it`
- [ ] rite
  - reverse_iterator operateurs `+` et `-`
- [ ] rite_eq_ope
  - dependance `rite` et `ite_eq_ope`
- [ ] size
  - dependance `enable_if`
- [ ] swap
  - dependance `enable_if`

## Fix SEGV:


## Fix Output:

- [x] copy_construct
- [x] push_pop
- [ ] ite_eq_ope
- [x] at_const
- [x] at
- [ ] ite_arrow