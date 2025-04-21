(define/contract (find-words board words)
  (-> (listof (listof char?)) (listof string?) (listof string?))
  
  ;; Get dimensions of the board
  (define m (length board))
  (define n (length (car board)))
  
  ;; Define trie node structure with mutable hash
  (define (make-trie-node)
    (define node (make-hash))
    (hash-set! node 'is-end? #f)
    (hash-set! node 'word #f)
    (hash-set! node 'children (make-hash))
    node)
  
  ;; Build trie from words list
  (define root (make-trie-node))
  (for ([word words])
    (let loop ([node root] [chars (string->list word)])
      (if (null? chars)
          (begin
            (hash-set! node 'is-end? #t)
            (hash-set! node 'word word))
          (let* ([c (car chars)]
                 [children (hash-ref node 'children)]
                 [child (hash-ref children c #f)])
            (unless child
              (set! child (make-trie-node))
              (hash-set! children c child))
            (loop child (cdr chars))))))
  
  ;; Result list to store found words
  (define result '())
  
  ;; Create the visited array
  (define visited (make-vector m))
  (for ([i (in-range m)])
    (vector-set! visited i (make-vector n #f)))
  
  ;; Backtracking function to search words
  (define (search i j current-node)
    ;; Check boundary conditions
    (if (or (< i 0) (>= i m) (< j 0) (>= j n))
        (void) ;; Out of bounds
        (if (vector-ref (vector-ref visited i) j)
            (void) ;; Already visited
            (let* ([c (list-ref (list-ref board i) j)]
                   [children (hash-ref current-node 'children)]
                   [next-node (hash-ref children c #f)])
              (when next-node
                ;; Mark current cell as visited
                (vector-set! (vector-ref visited i) j #t)
                
                ;; If we found a complete word
                (when (hash-ref next-node 'is-end? #f)
                  (let ([word (hash-ref next-node 'word)])
                    (set! result (cons word result))
                    ;; Mark as found to avoid duplicates
                    (hash-set! next-node 'is-end? #f)))
                
                ;; Explore all four directions
                (search (+ i 1) j next-node) ;; Down
                (search (- i 1) j next-node) ;; Up
                (search i (+ j 1) next-node) ;; Right
                (search i (- j 1) next-node) ;; Left
                
                ;; Backtrack
                (vector-set! (vector-ref visited i) j #f))))))
  
  ;; Start search from every cell in the board
  (for* ([i (in-range m)]
         [j (in-range n)])
    (search i j root))
  
  ;; Return result sorted alphabetically
  (sort result string<?))
