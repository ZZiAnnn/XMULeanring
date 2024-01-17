#������MIPS�������������жϣ����Գ���        test3.asm                         ð�ݷ����򣨽������У��Ӵ�С��                       

#��������ʼ��ַ��						0                                                              ROM��Ӧ000H

#IRA�жϷ���������ڵ�ַ��				3400H     				ROM��Ӧ100H  ��3400H-3000H)/4=100H
#IRB�жϷ���������ڵ�ַ��				3800H    				ROM��Ӧ200H  ��3800H-3000H)/4=200H
#IRC�жϷ���������ڵ�ַ��				3C00H    				ROM��Ӧ300H  ��3C00H-3000H)/4=300H

#10������8��1��5��2��7��9��6��4��3��10����ŵ���ʼ��ַ��	0 =  0H     			RAM��Ӧ000H

#��ջ����ʼ��ַ��  						1024 = 400H                         		RAM��Ӧ100H   ��400H/4=100H��

main:
 	addi $s0,$zero,8                        #��1����=8�������޸ģ����浽(0)
 	sw $s0,0($zero)

 	addi $s0,$zero,1                        #��2����=1�������޸ģ����浽(4)
 	sw $s0,4($zero)

 	addi $s0,$zero,5                        #��3����=5�������޸ģ����浽(8)
 	sw $s0,8($zero)

 	addi $s0,$zero,2                        #��4����=2�������޸ģ����浽(12)
	sw $s0,12($zero)

 	addi $s0,$zero,7                        #��5����=7�������޸ģ����浽(16)
	sw $s0,16($zero)

 	addi $s0,$zero,9                        #��6����=9�������޸ģ����浽(20)
 	sw $s0,20($zero)

 	addi $s0,$zero,6                        #��7����=6�������޸ģ����浽(24)
 	sw $s0,24($zero)

 	addi $s0,$zero,4                        #��8����=4�������޸ģ����浽(28)
 	sw $s0,28($zero)

 	addi $s0,$zero,3                        #��9����=3�������޸ģ����浽(32)
 	sw $s0,32($zero)

 	addi $s0,$zero,10                      #��10����=10�������޸ģ����浽(36)
 	sw $s0,36($zero)

 	addi $s0,$zero,0                  	#$s0=0                             �������俪ʼ��ַ
 	addi $s1,$zero,36  	  	#$s1=36=10*4-4              �������������ַ 

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
	addi $s1,$zero,36                     #$s1=36=10*4-4   �������������ַ
 	beq $s0,$s1,loop2                    #���$s0=$s1����תloop2
 	beq $zero,$zero,sort_loop       #תsort_loop

loop2:
                lw $a0,0($zero)
                addi $v0,$zero,34                   #syscall��34�Ź��ܣ������������ʾa0��ֵ        0�ŵ�Ԫ��
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,4($zero)
                addi $v0,$zero,34                   #syscall��34�Ź��ܣ������������ʾa0��ֵ        4�ŵ�Ԫ��
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,8($zero)
                addi $v0,$zero,34                   #syscall��34�Ź��ܣ������������ʾa0��ֵ        8�ŵ�Ԫ��
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,12($zero)
                addi $v0,$zero,34                   #syscall��34�Ź��ܣ������������ʾa0��ֵ        12�ŵ�Ԫ��
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,16($zero)
                addi $v0,$zero,34                   #syscall��34�Ź��ܣ������������ʾa0��ֵ        16�ŵ�Ԫ��
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,20($zero)
                addi $v0,$zero,34                   #syscall��34�Ź��ܣ������������ʾa0��ֵ        0�ŵ�Ԫ��
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,24($zero)
                addi $v0,$zero,34                   #syscall��34�Ź��ܣ������������ʾa0��ֵ        4�ŵ�Ԫ��
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,28($zero)
                addi $v0,$zero,34                   #syscall��34�Ź��ܣ������������ʾa0��ֵ        8�ŵ�Ԫ��
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,32($zero)
                addi $v0,$zero,34                   #syscall��34�Ź��ܣ������������ʾa0��ֵ        12�ŵ�Ԫ��
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,36($zero)
                addi $v0,$zero,34                   #syscall��34�Ź��ܣ������������ʾa0��ֵ        16�ŵ�Ԫ��
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

 	beq $zero,$zero,loop2	  #תloop2             ��ѭ��







IRA:                                                       #IRA�жϷ���������ڵ�ַ��3400H       RAM��Ӧ100H         
	addi $sp,$zero,1024    	#push registers  ��Ҫ�����жϳ����õ��ļĴ�����$a0    $v0��       
  	sw $a0,0($sp)
  	sw $v0,4($sp)

 	addi   $a0,$0,0x1111         	#display  00001111
	addi   $v0,$0,34           	
	syscall          

                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop

 	addi   $a0,$0,0x6666         	#display  0000aaaa
	addi   $v0,$0,34           	
	syscall      
       	
  	lw $v0,4($sp)   		#pop registers
  	lw $a0,0($sp)

  	eret











IRB: 				#IRB�жϷ���������ڵ�ַ��3800H         RAM��Ӧ200H            
	addi $sp,$zero,1024    	#push registers  ��Ҫ�����жϳ����õ��ļĴ�����$a0    $v0��       
  	sw $a0,0($sp)
  	sw $v0,4($sp)

  	addi   $a0,$0,0x2222         	#display  00002222
	addi   $v0,$0,34           	
	syscall                 	

                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop

 	addi   $a0,$0,0x7777         	#display  00007777
	addi   $v0,$0,34           	
	syscall      

  	lw $v0,4($sp)   		#pop registers
  	lw $a0,0($sp)

  	eret










IRC: 				#IRC�жϷ���������ڵ�ַ��3C00H            RAM��Ӧ300H          
	addi $sp,$zero,1024    	#push registers  ��Ҫ�����жϳ����õ��ļĴ�����$a0    $v0��        
  	sw $a0,0($sp)
  	sw $v0,4($sp)

 	addi   $a0,$0,0x3333         	#display  00003333
	addi   $v0,$0,34           	
	syscall                 	

                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop

 	addi   $a0,$0,0x8888         	#display  00008888
	addi   $v0,$0,34           	
	syscall      

  	lw $v0,4($sp)   		#pop registers
  	lw $a0,0($sp)

  	eret



