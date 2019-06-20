delimiter //
create trigger takes_prereq_insert before insert on takes
for each row
begin
	if exists(
		select 1
        from prereq
        where prereq.course_id = NEW.course_id and
			not exists (
				select 1
                from takes
                where prereq.prereq_id = takes.course_id and
					NEW.ID = takes.ID and
					takes.grade <> 'F' and
					takes.grade is not null
            )
    ) then
		signal sqlstate '45001' set message_text = "Prerequisite course not learned.";
    end if;
end;