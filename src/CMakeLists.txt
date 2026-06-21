target_sources(tick PRIVATE
  main.c
  screen.c
  element.c
  font.c
  clock.c
)

add_subdirectory(fonts)
add_subdirectory(screens)
add_subdirectory(elements)
