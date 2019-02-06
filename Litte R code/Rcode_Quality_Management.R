a = ss.data.batteries
b = ss.data.pc
b1 = ss.data.pc.r


with(ss.data.pc, barplot(pc.density, names.arg = pc.batch, las=2, main = "Barplot of volume ", sub = "Printer Cartridge"))

hist(ss.data.pc$pc.volume, main = "Histogram", xlab = "Volume", col="#efefef")

plot(pc.volume ~ pc.density, data = ss.data.pc, main = "Searching correlation between Density and Volume", col = "#000000", pch = 20, sub = "Printer Cartridge Example", xlab = "Volume of Ink", ylab = "Density")

my.bx <- boxplot(ss.data.pc$pc.volume~pc.filler, data = ss.data.pc, main = "Printer Catridge", sub = "Printer Cartridge Example", ylab = "Volume",xlab = "Filler", range = 0.7 )

help("text")

my.bp <- boxplot(ss.data.pc$pc.volume, col = "#CCCCCC",main = "Box Plot of Volume", sub = "Printer Cartridge Example", ylab = "Volume",range = 0.7)
text (x = rep(1, length(my.bp$out)), y = my.bp$out, labels = which(ss.data.pc$pc.volume==my.bp$out), pos = 4)
str(my.bp)
