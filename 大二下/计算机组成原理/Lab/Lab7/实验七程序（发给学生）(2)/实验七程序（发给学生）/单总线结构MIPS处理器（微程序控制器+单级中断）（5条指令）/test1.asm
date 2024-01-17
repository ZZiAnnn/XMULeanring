#MIPS����    test1.asm    ð�ݷ����򣨽������У��Ӵ�С��                       

#��������ʼ��ַ��0                                                                			RAM��Ӧ000

#IRQ0�жϷ���������ڵ�ַ��1024  =  400H     				RAM��Ӧ100                 
#IRQ1�жϷ���������ڵ�ַ��1536  =  600H     				RAM��Ӧ180
#IRQ2�жϷ���������ڵ�ַ��2048  =  800H    				RAM��Ӧ200
#IRQ3�жϷ���������ڵ�ַ��2560  =  A00H    				RAM��Ӧ280

#10������8��1��5��2��7��9��6��4��3��10����ŵ���ʼ��ַ��3072          	RAM��Ӧ300

#IRQ0�жϷ�����򽫵�ַΪ3328�Ĵ洢��Ԫ�����ݼ�1         			RAM��Ӧ340
#IRQ0�жϷ�����򽫵�ַΪ3392�Ĵ洢��Ԫ�����ݼ�1         			RAM��Ӧ350
#IRQ0�жϷ�����򽫵�ַΪ3456�Ĵ洢��Ԫ�����ݼ�1         			RAM��Ӧ360
#IRQ0�жϷ�����򽫵�ַΪ3520�Ĵ洢��Ԫ�����ݼ�1         			RAM��Ӧ370

#��ջ����ʼ��ַ��  3840                           				RAM��Ӧ3c0




.text  

main:
 	addi $s0,$zero,8                        #��1����=8�������޸ģ����浽(3072+0)
 	sw $s0,3072($zero)

 	addi $s0,$zero,1                        #��2����=1�������޸ģ����浽(3072+4)
 	sw $s0,3076($zero)

 	addi $s0,$zero,5                        #��3����=5�������޸ģ����浽(3072+8)
 	sw $s0,3080($zero)

 	addi $s0,$zero,2                        #��4����=2�������޸ģ����浽(3072+12)
	sw $s0,3084($zero)

 	addi $s0,$zero,7                        #��5����=7�������޸ģ����浽(3072+16)
	sw $s0,3088($zero)

 	addi $s0,$zero,9                        #��6����=9�������޸ģ����浽(3072+20)
 	sw $s0,3092($zero)

 	addi $s0,$zero,6                        #��7����=6�������޸ģ����浽(3072+24)
 	sw $s0,3096($zero)

 	addi $s0,$zero,4                        #��8����=4�������޸ģ����浽(3072+28)
 	sw $s0,3100($zero)

 	addi $s0,$zero,3                        #��9����=3�������޸ģ����浽(3072+32)
 	sw $s0,3104($zero)

 	addi $s0,$zero,10                      #��10����=10�������޸ģ����浽(3072+36)
 	sw $s0,3108($zero)

 	addi $s0,$zero,3072                  #$s0=3072                              �������俪ʼ��ַ
 	addi $s1,$zero,3108  	  #$s1=3108=3072+10*4-4       �������������ַ         

sort_loop:
 	lw $s3,0($s0)                     	  #$s3=($s0)
	lw $s4,0($s1)                	  #$s4=($s1)
 	slt $t0,$s3,$s4                	  #���$s3<$s4������$t0=1��������$t0=0        ��������         �Ӵ�С
 	beq $t0,$zero,sort_next   	  #���$t0=0����תsort_nent       
 	sw $s3,0($s1)                	  #����($s0)��($s1)
	sw $s4,0($s0)                   	  #����($s0)��($s1)

sort_next:
	addi $s1,$s1,-4                          #$s1-4 -> $s1
 	beq $s0,$s1,loop1                     #���$s0=$s1����תloop1   
 	beq $zero,$zero,sort_loop        #תsort_loop

loop1:
  	addi $s0,$s0,4                           #$s0+4 -> $s0
	addi $s1,$zero,3108                 #$s1=3108=3072+10*4-4   �������������ַ                     
 	beq $s0,$s1,loop2                    #���$s0=$s1����תloop2
 	beq $zero,$zero,sort_loop       #תsort_loop

loop2:
 	beq $zero,$zero,loop2	  #תloop2             ��ѭ��







IRQ0:                                                       #IRQ0�жϷ���������ڵ�ַ��1024   =   400H    		RAM��Ӧ100            
	addi $sp,$zero,3840    	#push registers  ��Ҫ�����жϳ����õ��ļĴ���                 $s0    $s1       
  	sw $s0,0($sp)
  	sw $s1,4($sp)

  	addi $s1,$zero,3328              #RAM��Ӧ340
  	lw $s0,0($s1)
  	addi $s0,$s0,1
  	sw $s0,0($s1)

  	lw $s1,4($sp)   		#pop registers
  	lw $s0,0($sp)
  	eret







IRQ1: 				#IRQ0�жϷ���������ڵ�ַ��1536     =   600H  		RAM��Ӧ180            
	addi $sp,$zero,3840    	#push registers  ��Ҫ�����жϳ����õ��ļĴ���                 $s0    $s1       
  	sw $s0,0($sp)
  	sw $s1,4($sp)

  	addi $s1,$zero,3392              #RAM��Ӧ350
  	lw $s0,0($s1)
  	addi $s0,$s0,1
  	sw $s0,0($s1)

  	lw $s1,4($sp)   		#pop registers
  	lw $s0,0($sp)
  	eret





IRQ2: 				#IRQ0�жϷ���������ڵ�ַ��2048       =  800H			RAM��Ӧ200            
	addi $sp,$zero,3840    	#push registers  ��Ҫ�����жϳ����õ��ļĴ���      	$s0    $s1        
  	sw $s0,0($sp)
  	sw $s1,4($sp)

  	addi $s1,$zero,3456             #RAM��Ӧ360
  	lw $s0,0($s1)
  	addi $s0,$s0,1
  	sw $s0,0($s1)

  	lw $s1,4($sp)   		#pop registers
  	lw $s0,0($sp)
  	eret





IRQ3: 				#IRQ0�жϷ���������ڵ�ַ��2560       =  A00H		RAM��Ӧ280            
	addi $sp,$zero,3840    	#push registers  ��Ҫ�����жϳ����õ��ļĴ���              $s0    $s1          
  	sw $s0,0($sp)
  	sw $s1,4($sp)

  	addi $s1,$zero,3520               #RAM��Ӧ370
  	lw $s0,0($s1)
  	addi $s0,$s0,1
  	sw $s0,0($s1)

  	lw $s1,4($sp)   		#pop registers
  	lw $s0,0($sp)
  	eret



