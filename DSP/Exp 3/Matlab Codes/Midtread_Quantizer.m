% Egemen Can Ayduðan - 21728036 
% PRELIMINARY WORK 3

function Quantized = Midtread_Quantizer(Signal,Bit)

X_AbsoluteMax = max(abs(Signal));      % Find the highest magnitude used
Delta = (2*X_AbsoluteMax)/(2^(Bit)) ;  % Our step size
LevelQuantization = (2^(Bit-1));       % How many levels we have in one side of the quatization graph
                   
for i=1 : length(Signal)
    imp(i) = abs(round(Signal(i)/Delta));
    if imp(i)< LevelQuantization
        Quantized(i) = (round(Signal(i)/Delta))*Delta;
    elseif Signal(i)>0
        Quantized(i) = (LevelQuantization-1)*Delta;
    elseif Signal(i)<0
        Quantized(i) = (-LevelQuantization)*Delta;
    elseif Signal(i) == 0
        Quantized(i) = 0;
    end
end
end
