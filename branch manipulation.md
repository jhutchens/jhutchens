#Manipulating branches with git

####Creating a remote branch:

git checkout -b <branchName>
\n... edit files, add and commit ...
\ngit push -u <branchName>


####Deleting a remote branch:

git push origin --delete <branchName>
