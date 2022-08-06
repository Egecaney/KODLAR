% Egemen Can Ayduðan - 21728036 
% PRELIMINARY WORK 1

function [FrequencyAxis,XDiscreteFT ] = DFT_Function(x,Ws)

Fs = Ws/(2*pi);
XDiscreteFT = fftshift(abs(fft(x)));
FrequencyAxis = (-Fs/2):(Fs/length(XDiscreteFT)):(Fs/2 - Fs/length(XDiscreteFT));

end
