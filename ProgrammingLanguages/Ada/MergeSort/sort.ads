package Sort is

    SIZE : constant Integer  := 40;
    SubType v_range is Integer Range -500..500;
    type m_array is array(1..SIZE) of v_range;

    procedure MergeSort(A : in out m_array);
    
    -- Internal functions
    procedure MergeSort(A : in out m_array; startIndex : Integer; endIndex : Integer);
    procedure ParallelMergeSort(A : in out m_array; startIndex : Integer; midIndex : Integer; endIndex : Integer);
    procedure Merge(A : in out m_array; startIndex, midIndex, endIndex : in Integer);

end sort;

