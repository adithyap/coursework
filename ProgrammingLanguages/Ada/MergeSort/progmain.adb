with Text_Io;
with sort;

-- ------------------
procedure progmain is
	
	-- Package usage declarations
	use Text_Io;
	use sort;
	package Int_Io is new Integer_Io(Integer);
	use Int_Io;

	-- Variable declarations
	A : m_array;
	input_var : Integer;
	array_sum : Integer;

	-- Task declarations
	task Reader is
		entry start;
	end Reader;

	task Sum is
		entry start;
	end Sum;

	task Printer is
		entry start;
	end Printer;

	-- Task definitions

	-- -----------------
	task body Reader is
	begin
		accept start do

			for i in 1..SIZE loop
				Int_Io.Get(input_var);
				A(i) := input_var;
			end loop;

		end start;
	end Reader;
	-- -----------------

	-- -----------------
	task body Sum is
	begin
		accept start do
			null;
		end start;

		array_sum := 0;

		for i in 1..SIZE loop
			array_sum := array_sum + A(i);
		end loop;

		Put("Array sum: ");
		Int_Io.Put(array_sum);

	end Sum;
	-- -----------------

	-- -----------------
	task body Printer is
	begin
		accept start do
			null;
		end start;

		Put("Sorted array: ");
		New_Line;

		for i in 1..SIZE loop
			Int_Io.Put(A(i));
		end loop;

	end Printer;
	-- -----------------

begin

	Reader.start;

	MergeSort(A);

	Sum.start;
	Printer.start;

end progmain;
-- ------------------
