(* -------------------------------------------------------------- *)
(* Pre-requisites *)
Control.Print.printDepth := 100;
Control.Print.printLength := 100;
(* -------------------------------------------------------------- *)




(* -------------------------------------------------------------- *)
(* Question 1 *)
(* Partition *)

(* Recursively call partition on the tail of the list,
   store them locally and merget the first element to the
   partitioned lists. *)

fun partition pivot [] = ([], [])
 | partition pivot (first::rest) =
	let
		val (low, high) = partition pivot rest
	in
		if first < pivot
		then 
			(first::low, high)
		else
			(low, first::high)
	end;

(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)
(* Test cases *)
(* partition 6 [5,2,8,4,1,9,6,10]; *)
(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)

(* End Question 1 *)
(* -------------------------------------------------------------- *)




(* -------------------------------------------------------------- *)
(* Question 2 *)
(* Partition Sort *)

(* Partition around the first element, 
   then call sort on the two partitioned lists *)

fun partitionSort [] = []
 | partitionSort (x::xs) = 
 	let
 		val (left,right) = partition x xs
 	in
 		(partitionSort left) @ [x] @ (partitionSort right)
 	end;

(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)
(* Test cases *)
(* partitionSort [5,2,9,10,12,4,8,1,19]; *)
(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)

(* End Question 2 *)
(* -------------------------------------------------------------- *)





(* -------------------------------------------------------------- *)
(* Question 3 *)
(* Generic Sort *)

(* Partition around the first element, 
   then call sort on the two partitioned lists *)

fun sort c [] = []
 | sort c (x::xs) = 
 	let
 		fun partition c pivot [] = ([], [])
		 | partition c pivot (first::rest) =
			let
				val (low, high) = partition c pivot rest
			in
				if c (first, pivot)
				then 
					(first::low, high)
				else
					(low, first::high)
			end;

 		val (left,right) = partition c x xs
 	in
 		(sort c left) @ [x] @ (sort c right)
 	end;

(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)
(* Test cases *)
(* sort (op <) [1,9, 3, 6, 7]; *)
(* sort (fn(a,b) => length a < length b) [[1, 9, 3, 6], [1], [2,4,6], [5,5]]; *)
(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)

(* End Question 3 *)
(* -------------------------------------------------------------- *)





(* -------------------------------------------------------------- *)
(* Question 4 *)
(* Binary Tree *)

(* Tree can be empty or a node or a leaf *)

datatype tree = empty | leaf of int | node of (int * tree * tree);

(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)
(* Test cases *)
(* val myTree = node(5,node(2,leaf 3,empty), node(12,node(8,leaf 7,leaf 11), 
                    node(4,leaf 1, node(6,empty, leaf 9)))); *)
(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)

(* End Question 4 *)
(* -------------------------------------------------------------- *)





(* -------------------------------------------------------------- *)
(* Question 5 *)
(* Max Tree *)

(* Store the max from left and right sub-tree in local variables. *)
(* Compare them with the node's value. *)
(* Handle empty leaves through if statements to avoid
   exception being raised. *)

exception emptyTreeException;

fun maxTree c empty = raise emptyTreeException
 | maxTree c (leaf x) = x
 | maxTree c (node (v,l,r)) = 
 	let
 		val left = if (l=empty) then v else maxTree c (l)
 		val right = if (r=empty) then v else maxTree c (r)
 	in
 		if c(v, left)
 		then
 			if c(v, right)
 			then
 				v
 			else
 				right
 		else
 			if c(left, right)
 			then
 				left
 			else
 				right
 	end;

(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)
(* Test cases *)
(* maxTree (op <) myTree; *)
(* maxTree (op >) myTree; *)
(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)

(* End Question 5 *)
(* -------------------------------------------------------------- *)





(* -------------------------------------------------------------- *)
(* Question 6 *)
(* Tree Traversal *)

(* Handle empty leaves through if statements to avoid
   exception being raised. *)
(* Preorder -- [v] @ preorder(l) @ preorder(r) *)
(* Inorder -- inorder(l) @ [v] @ inorder(r) *)
(* Postorder -- postorder(l) @ postorder(r) @ [v] *)

fun preorder empty = raise emptyTreeException
 | preorder (leaf x) = [x]
 | preorder (node (v,l,r)) = 
 	if (l=empty)
 	then
 		if (r=empty)
 		then
 			[v]
 		else
 			[v] @ preorder(r)
 	else	
 		if (r=empty)
 		then
 			[v] @ preorder(l)
 		else
 			[v] @ preorder(l) @ preorder(r)
 	;

 fun inorder empty = raise emptyTreeException
 | inorder (leaf x) = [x]
 | inorder (node (v,l,r)) = 
 	if (l=empty)
 	then
 		if (r=empty)
 		then
 			[v]
 		else
 			[v] @ inorder(r)
 	else
 		if (r=empty)
 		then
 			inorder(l) @ [v]
		else
 			inorder(l) @ [v] @ inorder(r)
 	;


 fun postorder empty = raise emptyTreeException
 | postorder (leaf x) = [x]
 | postorder (node (v,l,r)) = 
 	if (l=empty)
 	then
 		if (r=empty)
 		then
 			[v]
 		else
 			postorder(r) @ [v]
 	else
 		if (r=empty)
 		then
 			postorder(l) @ [v]
 		else
 			postorder(l) @ postorder(r) @ [v]
 	;

fun Labels ordering myTree = ordering(myTree);

(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)
(* Test cases *)
(* Labels preorder myTree; *)
(* Labels inorder myTree; *)
(* Labels postorder myTree; *)
(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)

(* End Question 6 *)
(* -------------------------------------------------------------- *)





(* -------------------------------------------------------------- *)
(* Question 7 *)
(* Lexicographic less than *)

(* If any of the array is empty, the other is larger. *)
(* If both are not empty, then compare the first elements and
   recurse into the tail of both of them as required. *)

fun lexLess c [] [] = false
 | lexLess c x [] = false
 | lexLess c [] x = true
 | lexLess c (x::xs) (y::ys) = 
 	if c(x, y)
 	then
 		true
 	else
 		if c(y, x)
 		then
 			false
 		else
 			lexLess c xs ys
 	;

(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)
(* Test cases *)
(* lexLess (op <) [1,2,3,4] [1,2,3,4,5]; *)
(* lexLess (op <) [1,2,3,4] [1,2,3]; *)
(* lexLess (fn(L1,L2) => length L1 < length L2) 
          [[3,4,5,6],[1,2,4]] [[1,2,3,4],[1,2,3,4]]; *)
(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)

(* End Question 7 *)
(* -------------------------------------------------------------- *)





(* -------------------------------------------------------------- *)
(* Question 8 *)
(* Tree sort *)

(* Call sort with a custom comparator. *)
(* Comparator uses LexLess on inorder traversals of two trees. *)

fun sortTreeList c x =
	sort (fn (a, b) => lexLess c (Labels inorder a) (Labels inorder b)) x
	;

(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)
(* Test cases *)
(* val t1 = node(5,node(4,node(2,leaf 1, leaf 3), empty),
                  node (7,leaf 6, empty)); *)
(* val t2 = node (5,node(4,node (2,node(1,leaf 0, empty),leaf 3),empty),
                   node (7,leaf 6,empty)); *)
(* val t3 = node(5,node(4,node(2,leaf 1, leaf 3), empty), leaf 6); *)
(* sortTreeList (op <) [t1, t2, t3]; *)
(* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *)

(* End Question 8 *)
(* -------------------------------------------------------------- *)
