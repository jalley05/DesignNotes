%%
%% Simple FIR filter example low pass
%%

lpf = fir1(numTaps-1, fc);
signalOut = conv(lpf, signalIn);
signalFinal = signalOut(numTaps/2:(taps/2+signalLength-1));


