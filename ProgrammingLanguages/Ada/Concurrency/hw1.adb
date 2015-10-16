with Text_Io;

-- ------------------
procedure hw1 is
	
	-- Package usage declarations
	use Text_Io;
	package Int_Io is new Integer_Io(Integer);
	use Int_Io;

	-- Task declarations
	task T1 is
		entry start;
	end T1;

	task T2 is
		entry start;
	end T2;

	-- Task definitions

	-- -----------------
	task body T1 is
	begin

			for i in 1..500 loop

				-- if i > 1 and ((i - 1) mod 50) = 0 then
				if ((i - 1) mod 50) = 0 then
					accept start do
						null;
					end start;
				end if;

				Int_Io.Put(i);

				if i mod 50 = 0 then
					T2.start;
				end if;

			end loop;
	end T1;
	-- -----------------

	-- -----------------
	task body T2 is
	begin

		T1.start;

		for i in 501..1000 loop

			if ((i - 1) mod 50) = 0 then
					accept start do
						null;
					end start;
			end if;

			Int_Io.Put(i);

			if i mod 50 = 0 then
					T1.start;
			end if;

		end loop;

	end T2;
	-- -----------------

begin

	null;

end hw1;
-- ------------------
