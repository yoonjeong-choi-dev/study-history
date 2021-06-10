import cProfile
import main

print("==========================================")
print("Use List")
cProfile.run("main.find_palingram_in_dictionary()")
print("==========================================\n")

print("==========================================")
print("Use Set")
cProfile.run("main.find_palingram_in_dictionary_improved()")
print("==========================================\n")
