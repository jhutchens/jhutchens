#Manipulating branches with git

####Creating a remote branch:

_git checkout -b branchName_

... edit files, add and commit ...

_git push -u branchName_


####Deleting a remote branch:

_git push origin --delete branchName_



####Merging a branch into master

1. Checkout the master branch: 

   _git checkout master_
   
2. Merge the branch into master: 

   _git merge branchName_
