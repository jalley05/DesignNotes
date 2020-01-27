%%
%% Simple sine wave with given number of cycles
%%
cycles = 10;
rad = 2*pi*cycles;
t = [0:0.1:rad];
signal = sin(t);

%%
%% With noise given number of samples
%%
samples = 1000;
Fs = 100GS/s;
T = 1/Fs;
t = (0:samples-1)*T;
signal = sin(2*pi*Hz*t);

