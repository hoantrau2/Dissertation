% clc;
% close all;
% clear all;
% 
% get_param('sim_model/Gain', 'Gain');
% set_param('sim_model/Gain', 'Gain', '50');
% 
% for gainVal = 0:50
%     gainVal
%     set_param('sim_model/Gain', 'Gain', int2str(gainVal));
%     pause(2);
% end

sampleTime = 0.01;
numSteps = 1001;
time = sampleTime*(0:numSteps-1);
time = time';
data = sin(2*pi/3*time);
simin = timeseries(data, time);
