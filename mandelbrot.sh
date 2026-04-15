g++ -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -g -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat \
 -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion \
 -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 \
 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self \
 -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 \
 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default \
 -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix \
 -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new \
 -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging \
 -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla \
 mandelbrot.cpp mandelbrot_intrince.cpp draw_frame.cpp start_view.cpp grafic_init.cpp draw_text.cpp click_processing.cpp destroy.cpp create_param.cpp\
 sdl_color.cpp intrince.cpp $(sdl2-config --cflags --libs) -lSDL2_ttf -O3 -o run