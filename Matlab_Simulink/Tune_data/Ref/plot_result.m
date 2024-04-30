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
ee = [];
index = [];

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
    
%     d(i) = sqrt((y_ref(i)-y(i))^2+(x_ref(i)-y(i))^2);
%     ee(i) = numbers(6,1)*180/pi;
    index(i) = numbers(7,1);
     
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
legend('ref', 'actual');
% xlim([-2, 2]);  
% ylim([-2, 2]);  
xlabel('y [m]')
ylabel('x [m]')
grid on
title("Result")

% creat axis time
timee = [];
num_sample = size (ee);
num_sample = num_sample(2);
timee(1) = 0;
for j = 2:num_sample
   timee(j) = (j-1)*sample_time;
end
%%%%%%%%%%%%
figure()
plot(timee,ee, 'k');
hold on
xlabel('time [s]')
ylabel('error angle [degree]')
grid on
title("Result angle")
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
xlabel('time [s]')
ylabel('error distance [m]')
grid on
title("Result distance")


%%%%%%%%%%%%%%%%%%%%%%%%%%%

error_dis = error_dis/num_sample
