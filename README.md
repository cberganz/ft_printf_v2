<div class="tg-wrap">
<img align="left" width=250px src="https://i.ibb.co/R00M5HK/printf.png" alt="printf" border="0">
<br><br>
 <table>
 <thead>
   <tr>
     <th>Project name</th>
     <th>ft_printf</th>
   </tr>
 </thead>
 <tbody>
   <tr>
     <td>Description</td>
     <td align="center">Custom version of the libc printf function</td>
   </tr>
   <tr>
     <td>Technologies</td>
     <td align="center"><a href="#"><img alt="C" src="https://custom-icon-badges.demolab.com/badge/C-03599C.svg?logo=c-in-hexagon&logoColor=white&style=for-the-badge"></a></td>
   </tr>
   <tr>
      <td>Allowed libraries</td>
      <td>malloc(), free(), write(), va_start(), va_arg(), va_copy(), va_end()</td>
   </tr>
 </tbody>
 </table>
</div>
<br>

## Usage
#### Generate the library
```
git clone https://github.com/cberganz/ft_printf_v2_remastered.git ft_printf
make -C ft_printf
```
#### Use the library
-> Link the library inside the Makefile of your project
```
$(CC) $(CFLAGS) -Lft_printf -lftprintf -c $< -o $@
```
#### Use the function
```c
int main(int argc, char *argv[])
{
  ft_printf("%42.42d\n", 42);
  return 0;
}
```
