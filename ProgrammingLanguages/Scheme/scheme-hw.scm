;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Scheme Programming Assignment
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Solutions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Question 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; (fromTo k n)     Returns the list of integers from k to n. The size
;;                  of the problem can be seen as the difference
;;                  between k and n.
;;
;; Base Case:       If k = n , then the result is the list containing only n
;;                  If k > n, then return an empty list
;;
;; Hypothesis:      Assume (fromTo (+ k 1) n) returns the list of integers
;;                  from k+1 to n.
;;
;; Recursive step: (fromTo k n) = (cons k (FromTo (+ k 1) n)
;;

(define (fromTo k n) 
        (cond ( (= k n) (list n) )
              ( (> k n) '() )
              (else fromTo (cons k (fromTo (+ k 1) n)))
              )
  )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Question 2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; (removeMults m L) returns a list containing all elements of L which
;;                   are not a multiple of m
;;
;; Base Case:        If list size is zero, return empty list
;;
;; Hypothesis:       Assume (removeMults m (cdr L)) returns the list of
;;                   non-multiples of m from the (cdr L)
;;
;; Recursive step:   (removeMults m L) = ( (if (= (modulo (car L) m) 0)
;;                                       (removeMults m (cdr L))
;;                                       (cons (car L) (removeMults m (cdr L))) ) )

(define (removeMults m L)
        (cond ((null? L) '() )
              ((= (modulo (car L) m) 0) (removeMults m (cdr L)) )
              (else (cons (car L) (removeMults m (cdr L))) )
              )
        )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Question 3
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; (removeAllMults L)     Given that the input is strictly increasing,
;;                        returns a list containing elements that are
;;                        not a multiple of each other
;;
;; Base Case:             If the list is empty, return empty list
;;
;; Hypothesis:            Assume (removeAllMults m (cdr L)) returns a
;;                        list of non-mutual multiples from the (cdr L)
;;
;; Recursive Step:        [assumes (removeMults m L) works]
;;                        (cons (car L) (removeAllMults
;;                                    (removeMults (car L) (cdr L) ) ) )
;;

(define (removeAllMults L)
        (cond ((null? L) '() )
              (else (cons (car L) (removeAllMults (removeMults (car L) (cdr L) ) ) ) )
          )
 )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Question 4
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; (primes n)        Computes the list of all primes
;;                   less than or equal to n
;;
;; Base Case:        If n is 2, return a list containing 2
;;                   If n is less than 2, return an empty list
;;
;; Hypothesis:       Assume (primes (- n 1)) returns a list of
;;                   all primes upto n + 1
;;
;; Recursive Step:   (removeAllMults (append (primes (- n 1)) (list n)) )
;;                   Remove all mutual multiples of n in the list,
;;                   (primes (- n 1)) and (n), leaving only the primes.
;;                   (since no smaller number can be multiplied to obtain
;;                   a prime number)
;;

(define (primes n)
        (cond ((< n 2 ) '())
              ((= n 2 ) (list 2))
              (else (removeAllMults (append (primes (- n 1)) (list n)) ) )
              )
  )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Question 5
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; (maxDepth L)    Returns the maximum nesting depth of any element within L
;;
;; Base Case:      There are two potential base cases
;;                 a. List is null, return 0
;;                 b  If the input is not a list, but a number, return -1
;;                    Note: This is chosen since the problem specifies that
;;                          a list with no depth is 0, so logically, an element
;;                          in it is chosen as -1. This is also used in the
;;                          recursive step
;;
;; Hypothesis:     Assume maxDepth works on all the possible nested lists in L
;;
;; Recursive Step: Height of each level is the max-height of each of its
;;                 elements plus one
;;                 (+ (apply max (map maxDepth L) ) 1 )
;;                 [apply is used to apply (max) on a list]
;;

(define (maxDepth L)
        (cond ((null? L) 0)
              ((not (list? L)) -1)
              (else (+ (apply max (map maxDepth L) ) 1 ))
              )
  )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Question 6
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; (prefix exp)    Transforms an infix arithmetic expression exp into prefix notation
;;
;; Base Case:      There are three potential base cases
;;                 a. List is null, return empty list
;;                 b  If the input is not a list, just return it
;;                 c. If the input is a single element list, return that element
;;
;; Hypothesis:     If we look at an infix epression as (E1 SYMBOL E2), we assume that
;;                 prefix on E1 and E2 work
;;
;; Recursive Step: prefix = (list (cadr exp) (prefix (car exp)) (prefix (cddr exp)) )
;;

(define (prefix exp) 
        (cond ((null? exp) '())
              ((not (list? exp)) exp )
              ((null? (cdr exp)) (car exp) )
              (else (list (cadr exp) (prefix (car exp)) (prefix (cddr exp)) ))
              )
  )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Question 7
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; (composition fns) Takes a list of functions fns and returns
;;                   a function that is the composition of the functions in fns
;;
;; Base Case:        The the list contains only one function,
;;                   invoke that one function as a lambda with one parameter
;;
;; Hypothesis:       Assume that composition works on the (cdr fns)
;;
;; Recursive Step:   (lambda (x) ( (car fns) ((composition (cdr fns)) x) ) )
;;                   Which is, return a lambda expression where we invoke the
;;                   (car fns) with the composition of (cdr fns)
;;

(define (composition fns)
        (cond ((null? (cdr fns)) (lambda (x) ((car fns) x)))
              (else (lambda (x) ( (car fns) ((composition (cdr fns)) x) ) ) )
         )
  )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End Solutions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; +++++++++++++++++++++++++++++++ Test Cases +++++++++++++++++++++++++++++++
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Question 1
;;
;;(fromTo 3 8)
;;(fromTo 1 1)
;;(fromTo -4 1)
;;(fromTo 40 1)

;; Question 2
;;
;;(removeMults 17 '())
;;(removeMults 3 '(2 3 4 5 6 7 8 9 10))
;;(removeMults 200 '(200 400 600 800 1000))

;; Question 3
;;
;;(removeAllMults '())
;;(removeAllMults '(3 4 6 7 8 10 12 15 20 22 23))
;;(removeAllMults '(2 3 5 7 11))
;;(removeAllMults '(3 27 81 243 729))

;; Question 4
;;
;;(primes 1)
;;(primes 2)
;;(primes 30)
;;(primes 97)

;; Question 5
;;
;;(maxdepth '())
;;(maxdepth '(1 2 3))
;;(maxdepth '(1 (2 3) (4 4.1 4.2 (4.3 4.35 4.39) ) 5 6))
;;(maxdepth '((0 1) (2 (3 (4 5 (6 (7 8) 9) 10) 11 12) 13) (14 15)))

;; Question 6
;;
;;(prefix 3)
;;(prefix '(1))
;;(prefix '(3 + 4))
;;(prefix '((3 + 4) * 5))
;;(prefix '(3 + 4 * 5 - 6))
;;(prefix '((3 * 4) + (5 - 6) * 7))

;; Question 7
;;
;;(define f (composition (list (lambda (x) (+ x 1)) ))) ;; 1 function (not really a composition)
;;(define f (composition (list (lambda (x) (+ x 1)) (lambda (x) (* x 2))))) ;; 2 functions
;;(define f (composition (list (lambda (x) (+ x 1)) (lambda (x) (* x 2)) (lambda (x) (- x 1)) ))) ;; 3 functions
;;(f 10) ;; Invoke statement

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; +++++++++++++++++++++++++++++ End Test Cases +++++++++++++++++++++++++++++
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
