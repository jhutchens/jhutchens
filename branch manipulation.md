#Manipulating branches with git

####Creating a remote branch:

git checkout -b branchName

... edit files, add and commit ...

git push -u branchName


####Deleting a remote branch:

git push origin --delete branchName



####Merging a branch into master

1. Checkout the master branch (git checkout master)
2. Merge the target branch into master (git merge branchName)
