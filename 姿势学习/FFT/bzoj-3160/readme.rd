#solution

		答案 = 总回文子序列个数 - 回文子串个数
		回文子串个数由Manachar直接统计可得
		回文子序列个数 可枚举所有字符a,b
		令`x[i] = s[i] == ch ? 1 : 0;` 则枚举所有中心,对于每个中心统计答案的方式同卷积相似,直接FFT搞一遍即可