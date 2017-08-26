from filecmp import dircmp

def print_diff_files(dcmp):
  for name in dcmp.diff_files:
     print("diff_file %s found in %s and %s" % (name, dcmp.left,
            dcmp.right))
  for sub_dcmp in dcmp.subdirs.values():
     print_diff_files(sub_dcmp)

dcmp = dircmp(r'G:\Music', r'I:\Music')
print_diff_files(dcmp)
