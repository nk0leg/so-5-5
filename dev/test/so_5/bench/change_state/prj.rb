require 'mxx_ru/cpp'

MxxRu::Cpp::exe_target {

	required_prj 'ace/dll.rb'
	required_prj 'so_5/prj.rb'
	target '_test.bench.so_5.change_state'

	cpp_source 'main.cpp'
}