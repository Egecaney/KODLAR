% Egemen Can Ayduðan - 21728036 
% PRELIMINARY WORK 1

function [TimeAxis,Xdiscrete] = SinSamples(A,W,Teta,d,Ws)

SamplingFrequency = Ws/(2*pi);
TimeAxis = 0:1/SamplingFrequency:d-1/SamplingFrequency;
Xdiscrete = A*sin(W*TimeAxis+Teta);

end
