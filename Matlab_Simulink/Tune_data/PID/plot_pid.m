% open log file
fid = fopen('v_max.log', 'r');
fid_1 = fopen('pwm_max.log', 'r');
v1 = [];
v2 = [];
v3 = [];
v4 = [];
u1 = [];
u2 = [];
u3 = [];
u4 = [];
v = [];
w = [];
W = 0.2469;
% read first line in log file
tline = fgetl(fid);
i = 1;
tline_1 = fgetl(fid_1);
j = 1;
while ischar(tline)
    % conver to array 4x1
    numbers = textscan(tline, '%f', 'Delimiter', ',');
    numbers = numbers{1}; 
    % choose data 
    v1(i) = numbers(1,1);
    v2(i) = numbers(2,1);
    v3(i) = numbers(3,1);
    v4(i) = numbers(4,1);
    vl = (v1(i)+v2(i))/2;
    vr = (v3(i)+v4(i))/2;
    v(i) = (vl+vr)/2;
    w(i) = (vr-vl)/W;
    i = i+1;
    % read next line in log file
    tline = fgetl(fid);
end


% creat axis time and ref value
sample_time = 0.1;
time = [];
num_sample = size (v1);
num_sample = num_sample(2);
time(1) = 0;
vl_ref = zeros(size(v1));
vr_ref = zeros(size(v1));
vl_ref(1) = 0;
vr_ref(1) = 0;
for j = 2:num_sample
   time(j) = (j-1)*sample_time;
   % if time(j) <1
   %     vl_ref(j) = 0.6;
   %     vr_ref(j) = 0.6;
   % elseif time(j) <2
   %     vl_ref(j) = 0.6;
   %     vr_ref(j) = 0.6;
   % elseif time(j) < 15
   %     vl_ref(j) = 0.6;
   %     vr_ref(j) = 0.6;
   % else
   %     vl_ref(j) = 0;
   %     vr_ref(j) = 0;
   % end
   vl_ref(j) = 0.6;
   vr_ref(j) = 0.6;
end

v_ref = (vl_ref+vr_ref)/2;
w_ref = (-vl_ref+vr_ref)/W;


% Mean squared error
Error_1 = 0;
Error_2 = 0;
Error_3 = 0;
Error_4 = 0;
Error_v = 0;
Error_w = 0;

for i = 1:num_sample
    if time(i) > 5
        Error_1 = Error_1 + (vl_ref(i) - v1(i)).^2;
        Error_2 = Error_2 + (vl_ref(i) - v2(i)).^2;
        Error_3 = Error_3 + (vr_ref(i) - v3(i)).^2;
        Error_4 = Error_4 + (vr_ref(i) - v4(i)).^2;
        Error_v = Error_v + (v_ref(i) - v(i)).^2;
        Error_w = Error_w + (w_ref(i) - w(i)).^2;
    end
end
% Calculate mean squared error (MSE)
MSE_1 = Error_1 / num_sample;
MSE_2 = Error_2 / num_sample;
MSE_3 = Error_3 / num_sample;
MSE_4 = Error_4 / num_sample;
MSE_v = Error_v / num_sample;
MSE_w = Error_w / num_sample;

% Calculate root mean squared error (RMSE)
RMSE_1 = sqrt(MSE_1)
RMSE_2 = sqrt(MSE_2)
RMSE_3 = sqrt(MSE_3)
RMSE_4 = sqrt(MSE_4)
RMSE_v = sqrt(MSE_v)
RMSE_w = sqrt(MSE_w)


% calculate error
e1 = vl_ref - v1;
e2 = vl_ref - v2;
e3 = vr_ref - v3;
e4 = vr_ref - v4;
e_v = v_ref - v;
e_w = w_ref - w;

% read u
for j = 1:num_sample
    numbers = textscan(tline_1, '%f', 'Delimiter', ',');
    numbers = numbers{1}; 
    % choose data 
    u1(j) = numbers(1,1);
    u2(j) = numbers(2,1);
    u3(j) = numbers(3,1);
    u4(j) = numbers(4,1);
    % read next line in log file
    tline_1 = fgetl(fid_1);
end
% close file
fclose(fid_1);
%% motor 1
figure()
subplot(3, 1, 1);
plot(time,v1, 'k','LineWidth', 2);
hold on
xlabel('time [s]')
ylabel('velocity [m/s]')
grid on
title("Velocity motor 1")
% motor 2
subplot(3, 1, 2);
plot(time,v2, 'k','LineWidth', 2);
hold on
xlabel('time [s]')
ylabel('velocity [m/s]')
grid on
title("Velocity motor 2")
% motor 3
subplot(3, 1, 3);
plot(time,v1, 'k','LineWidth', 2);
hold on
xlabel('time [s]')
ylabel('velocity [m/s]')
grid on
title("Velocity motor 3")
% motor 4
figure()
subplot(2, 1, 1);
plot(time,v1, 'k','LineWidth', 2);
hold on
xlabel('time [s]')
ylabel('velocity [m/s]')
grid on
title("Velocity motor 4")
% linear velocity
subplot(2, 1, 2);
plot(time,v, 'k','LineWidth', 2);
hold on
xlabel('time [s]')
ylabel('velocity [m/s]')
grid on
title("Linear velocity")

%% %% motor 1
% figure()
% subplot(3, 1, 1);
% plot(time,v1, 'k','LineWidth', 2);
% hold on
% plot(time,vl_ref, 'r','LineWidth', 2);
% hold on
% legend('v real', 'v ref')
% xlabel('time [s]')
% ylabel('velocity [m/s]')
% grid on
% title("Velocity motor 1")
% 
% subplot(3, 1, 2);
% plot(time, e1, 'b','LineWidth', 2);
% hold on
% xlabel('time [s]')
% ylabel('error [m/s]')
% grid on
% title("Error velocity motor 1")
% 
% subplot(3, 1, 3);
% plot(time, u1, 'g','LineWidth', 2);
% xlabel('time [s]')
% ylabel('output pid')
% grid on
% title("Control signal motor 1")
% 
% 
% 
% %% motor 2
% figure()
% subplot(3, 1, 1);
% plot(time,v2, 'k','LineWidth', 2);
% hold on
% plot(time,vl_ref, 'r','LineWidth', 2);
% hold on
% legend('v real', 'v ref')
% xlabel('time [s]')
% ylabel('velocity [m/s]')
% grid on
% title("Velocity motor 2")
% 
% subplot(3, 1, 2);
% plot(time, e2, 'b','LineWidth', 2);
% hold on
% xlabel('time [s]')
% ylabel('error [m/s]')
% grid on
% title("Error velocity motor 2")
% 
% subplot(3, 1, 3);
% plot(time, u2, 'g','LineWidth', 2);
% xlabel('time [s]')
% ylabel('output pid')
% grid on
% title("Control signal motor 2")
% %% motor 3
% figure()
% subplot(3, 1, 1);
% plot(time,v3, 'k','LineWidth', 2);
% hold on
% plot(time,vl_ref, 'r','LineWidth', 2);
% hold on
% legend('v real', 'v ref')
% xlabel('time [s]')
% ylabel('velocity [m/s]')
% grid on
% title("Velocity motor 3")
% 
% subplot(3, 1, 2);
% plot(time, e3, 'b','LineWidth', 2);
% hold on
% xlabel('time [s]')
% ylabel('error [m/s]')
% grid on
% title("Error velocity motor 3")
% 
% subplot(3, 1, 3);
% plot(time, u3, 'g','LineWidth', 2);
% xlabel('time [s]')
% ylabel('output pid')
% grid on
% title("Control signal motor 3")
% %% motor 4
% figure()
% subplot(3, 1, 1);
% plot(time,v4, 'k','LineWidth', 2);
% hold on
% plot(time,vl_ref, 'r','LineWidth', 2);
% hold on
% legend('v real', 'v ref')
% xlabel('time [s]')
% ylabel('velocity [m/s]')
% grid on
% title("Velocity motor 4")
% 
% subplot(3, 1, 2);
% plot(time, e4, 'b','LineWidth', 2);
% hold on
% xlabel('time [s]')
% ylabel('error [m/s]')
% grid on
% title("Error velocity motor 4")
% 
% subplot(3, 1, 3);
% plot(time, u4, 'g','LineWidth', 2);
% xlabel('time [s]')
% ylabel('output pid')
% grid on
% title("Control signal motor 4")
% %% linear velocity
% figure()
% plot(time,v, 'k','LineWidth', 2);
% hold on
% plot(time,v_ref, 'r','LineWidth', 2);
% hold on
% plot(time, e_v, 'b','LineWidth', 2);
% legend('v real', 'v ref', 'error')
% xlabel('time [s]')
% ylabel('velocity [m/s]')
% grid on
% title("Linear velocity")
% %% angular velocity
% figure()
% plot(time,w, 'k','LineWidth', 2);
% hold on
% plot(time,w_ref, 'r','LineWidth', 2);
% hold on
% plot(time, e_w, 'b','LineWidth', 2);
% legend('w real', 'w ref', 'error')
% xlabel('time [s]')
% ylabel('angular velocity [m/s]')
% grid on
% title("Angular velocity")
