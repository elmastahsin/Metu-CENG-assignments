N=1503;
        lambda_Bulk = 50;
        lambda_Cont = 40;
        lambda_Tank = 25;
        totalWeight = zeros(N,1);

        for k=1:N
        U = rand; i=0;
        F = exp(-lambda_Bulk);
        while (U>=F)
        i=i+1;
        F = F + exp(-lambda_Bulk)*lambda_Bulk^i/gamma(i+1);
        end
        numberBulk = i;
        lambda_W_Bulk = 0.1;
        alphaBulk = 60;
        weightBulk = sum(-1/lambda_W_Bulk * log(rand(alphaBulk,numberBulk)));
        totalW_Bulk = sum(weightBulk);

        U = rand; i=0;
        F = exp(-lambda_Cont);
        while (U>=F)
        i=i+1;
        F = F + exp(-lambda_Cont)*lambda_Cont^i/gamma(i+1);
        end
        numberCont = i;
        lambda_W_Cont = 0.05;
        alphaCont = 100;
        weightCont = sum(-1/lambda_W_Cont * log(rand(alphaCont,numberCont)));
        totalW_Cont = sum(weightCont);

        U = rand; i=0;
        F = exp(-lambda_Tank);
        while (U>=F)
        i=i+1;
        F = F + exp(-lambda_Tank)*lambda_Tank^i/gamma(i+1);
        end
        numberTank = i;
        lambda_W_Tank = 0.02;
        alphaTank = 120;
        weightTank = sum(-1/lambda_W_Tank * log(rand(alphaTank,numberTank)));
        totalW_Tank = sum(weightTank);

        totalWeight(k) = totalW_Bulk + totalW_Cont + totalW_Tank;

        end

        p_est = mean(totalWeight>3000000);
        expectedWeight = mean(totalWeight);
        stdWeight = std(totalWeight);
        fprintf('Estimated probability = %f\n',p_est);
        fprintf('Expected weight = %f\n',expectedWeight);
        fprintf('Standard deviation = %f\n',stdWeight);