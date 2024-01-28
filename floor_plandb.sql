create table floor_plan.user
(
    user_name varchar(255),
    user_id int,
    pass_word varchar(200),
    primary key(user_id),
    user_role varchar(100),
    x int,
    y int,
    z int
);

create table floor_plan.room
(
    room_id int,
    primary key(room_id),
    capacity int,
    projector bit,
    x int,
    y int,
    z int
);
create table meeting_rooms
(
    meeting_id int,
    primary key(meeting_id),
    room_id int,
	foreign key(room_id)  references room(room_id),
    start_time timestamp,
    end_time timestamp
);

create table floor_plan.booking
(
    booking_id int,
    primary key(booking_id),
    meeting_id int,
    owner_id int,
    foreign key(meeting_id) references meeting_rooms(meeting_id),
    foreign key(owner_id)  references user(user_id)
);
create table floor_plan.meeting_members
(
     booking_id int,
     user_id int,
     primary key(booking_id,user_id),
     foreign key(user_id)  references user(user_id),
     foreign key(booking_id) references booking(booking_id)
);

create table admin
(
    admin_id int,
    admin_name varchar(255)
);
ALTER TABLE meeting_rooms
ADD admin_id int;
ALTER TABLE meeting_rooms
ADD  foreign key(admin_id) references admin(admin_id);
ALTER TABLE admin
add password int;
    
