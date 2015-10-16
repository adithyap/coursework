package body sort is

    -- ---------------------------------------
    procedure MergeSort(A : in out m_array) is
    begin

        if SIZE > 0 then
            MergeSort(A, 1, SIZE);
        end if;

    end MergeSort;
    -- ---------------------------------------

    -- ---------------------------------------
    procedure MergeSort(A : in out m_array; startIndex : Integer; endIndex : Integer) is

        midIndex : Integer := startIndex + (endIndex - startIndex) / 2;

    begin

        ParallelMergeSort(A, startIndex, midIndex, endIndex);

        Merge(A, startIndex, midIndex, endIndex);

    end MergeSort;
    -- ---------------------------------------

    -- ---------------------------------------
    procedure ParallelMergeSort(A : in out m_array; startIndex : Integer; midIndex : Integer; endIndex : Integer) is

        task MergeSortCall1;
        task MergeSortCall2;

        -- ------------------------
        -- Start to Mid
        -- ------------------------
        task body MergeSortCall1 is
        begin
            if startIndex < endIndex then
                MergeSort(A, startIndex, midIndex);
            end if;
        end MergeSortCall1;
        -- ------------------------

        -- ------------------------
        -- Mid + 1 to End
        -- ------------------------
        task body MergeSortCall2 is
        begin
            if startIndex < endIndex then
                MergeSort(A, midIndex + 1, endIndex);
            end if;
        end MergeSortCall2;
        -- ------------------------

    begin
        null;
    end ParallelMergeSort;
    -- ---------------------------------------

    -- ---------------------------------------
    procedure Merge(A : in out m_array; startIndex, midIndex, endIndex : in Integer) is

    	aux: m_array;
    	i, j: Integer;

    begin

    	i := startIndex;
    	j := midIndex + 1;

    	for k in startIndex..endIndex loop

    		if (i > midIndex) then

    			aux(k) := A(j);
    			j := j + 1;

    		elsif (j > endIndex) then
    			
    			aux(k) := A(i);
    			i := i + 1;

    		elsif (A(j) < A(i)) then
    			
    			aux(k) := A(j);
    			j := j + 1;

    		else
    			
    			aux(k) := A(i);
    			i := i + 1;

    		end if;

    	end loop;
    	
    	-- Copy from auxiliary array to main array
    	for k in startIndex..endIndex loop
    		A(k) := aux(k);
    	end loop;
    
    end Merge;
    -- ---------------------------------------

end sort;
