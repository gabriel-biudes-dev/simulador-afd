Para o funcionamento do programa, o usuário deve informar a lista de caracteres do alfabeto, a lista de estados, a lista de estados finais e a lista de transições da seguinte maneira:
Na primeira linha, deve estar definida a lista de caracteres no formato "alfabeto={a,b,...}"
Na segunda linha, deve estar definida a lista de estados no formato "estados={q0,q1,q2,...,qn}"
Na terceira linha, deve estar definida a lista de estados finais no formato "finais={q0,...,qn}"
Da quarta linha em diante, são definidas as transições do autômato, no formato "(qx,a)=qy", onde qx é o estado atual, 'a' é o caractere a ser lido e qy é o próximo estado