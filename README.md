# File-Organisation
Heap File Organisation


1. Insert - insert in an invalid directory location or an empty space (2 cases only - no clubbing of empty spaces, invalid directory locations etc.)

2. Search, Display - self understood

3. Delete - If found, set valid bit = 0, if this location has empty space following it, club it within the directory location (don't do it for the last directory location)
