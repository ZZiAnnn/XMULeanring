function F = my_DFT(fp)
    [M, N] = size(fp);
    x = 0:M-1;
    y = 0:N-1;
    u = x';
    v = y';

    eM = exp(-2j * pi * (u * x) / M);
    eN = exp(-2j * pi * (v * y) / N);

    F = eM * fp * eN;
end
