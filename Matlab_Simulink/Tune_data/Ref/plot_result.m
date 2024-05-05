% step = 0.3m, ee = 0.1 m, v = 0.2 m/s

% open log file
fid = fopen('data.log', 'r');
sample_time = 0.1;
x = [];
y = [];
angle_robot = [];

x_ref = [];
y_ref = [];
angle_ref = [];

d = [];
d_ = [];
ee = [];
index = [];
at =[];
sign =[];
error_dis = 0;

% read first line in log file
tline = fgetl(fid);
i = 1;
while ischar(tline)
    % conver to array 4x1
    numbers = textscan(tline, '%f', 'Delimiter', ',');
    numbers = numbers{1}; 
    % choose data 
    
    x(i) = numbers(1,1);
    y(i) = numbers(2,1);
    
    
    x_ref(i) = numbers(3,1);
    y_ref(i) = numbers(4,1);
    
   
%     d(i) = sqrt((x_ref(i)-x(i))^2+(y_ref(i)-y(i))^2);
    ee(i) = numbers(6,1)*180/pi;
    d(i) = numbers(5,1);
    at(i) =  numbers(9,1);
    sign(i) =  numbers(10,1);
%     d(i) = sqrt((y_ref(i)-y(i))^2+(x_ref(i)-y(i))^2);
    ee(i) = numbers(6,1)*180/pi;
    index(i) = numbers(7,1);
    angle_ref(i) = numbers(8,1)*180/pi;
%     if angle_ref(i) <0 
%         angle_ref(i)= angle_ref(i)+ 360;
%     end
    angle_robot(i) = angle_ref(i) -ee(i);
    
    
    
    error_dis = error_dis + d(i);
    
    i = i+1;
    % read next line in log file
    tline = fgetl(fid);
end


% close file
fclose(fid);

%% 
figure() 
plot(y_ref,x_ref, 'r');
hold on
plot(y,x, 'k');
hold on
% plot(time,e_dot, 'b');
legend('position ref', 'position actual');
% xlim([-1, 1]);  
% ylim([-1, 1]);  
xlabel('y [m]')
ylabel('x [m]')
grid on
title("Result Position")

% creat axis time
timee = [];
num_sample = size (ee);
num_sample = num_sample(2);
timee(1) = 0;
for j = 2:num_sample
   timee(j) = (j-1)*sample_time;
end
%% 
figure() 
plot(timee,angle_ref, 'r');
hold on
plot(timee,angle_robot, 'k');
hold on
legend('angle ref', ' angle actual');
% xlim([-2, 2]);  
% ylim([-2, 2]);  
xlabel('time [s]')
ylabel('angle [degree]')
grid on
title("Result Angle")
%%%%%%%%%%%%
figure()
plot(timee,ee, 'k');
hold on
xlabel('time [s]')
ylabel('error angle [degree]')
grid on
title("Result error angle")
%%%%%%%%%%%%
% creat axis time
timed = [];
num_sample = size (d);
num_sample = num_sample(2);
timed(1) = 0;
for j = 2:num_sample
   timed(j) = (j-1)*sample_time;
end
%%%%%%%%%%%%%%%
figure()
plot(timed,d, 'r');
hold on
% plot(timed, at, 'b');
% hold on
xlabel('time [s]')
ylabel('error distance [m]')
grid on
title("Result distance")

% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%
% figure()
% plot(timed,index, 'r');
% hold on
% xlabel('time [s]')
% ylabel('error distance [m]')
% grid on
% title("index")
% %%%%%%%%%%%%
% error_dis = error_dis/num_sample
% 
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% figure() 
% plot(timed,x_ref, 'r');
% hold on
% plot(timed,x, 'k');
% hold on
% % plot(time,e_dot, 'b');
% legend('position ref', 'position actual');
% % xlim([-1, 1]);  
% % ylim([-1, 1]);  
% xlabel('time [s]')
% ylabel('x [m]')
% grid on
% title("x")
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% figure() 
% plot(timed,y_ref, 'r');
% hold on
% plot(timed,y, 'k');
% hold on
% % plot(time,e_dot, 'b');
% legend('position ref', 'position actual');
% % xlim([-1, 1]);  
% % ylim([-1, 1]);  
% xlabel('time [s]')
% ylabel('y [m]')
% grid on
% title("y")
% %%%%%%%%%%%%%%%
% figure()
% plot(timed,sign, 'r');
% hold on
% plot(timed, at, 'b');
% hold on
% xlabel('time [s]')
% ylabel('---- [m]')
% grid on
% title("-----------")
