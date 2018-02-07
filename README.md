### Instructions

## Updating a git repo to a new branch 

Commit all outstanding change to a new branch.
```
git fetch
git checkout NEW_TAG_NAME
```

## Production Code


# Setup CMSSW 
```
setenv SCRAM_ARCH slc6_amd64_gcc630
cmsrel CMSSW_9_4_4
cd CMSSW_9_4_4/src/
cmsenv
git cms-init
```

# Check out the DeepAK8 code

```
# check out the package
git clone ssh://git@gitlab.cern.ch:7999/DeepAK8/NNKit.git

# setup mxnet library
cp NNKit/misc/*.xml $CMSSW_BASE/config/toolbox/$SCRAM_ARCH/tools/selected
scram setup openblas
scram setup mxnet
rm $CMSSW_BASE/external/$SCRAM_ARCH/lib/libmxnet.so
cp NNKit/misc/lib/libmxnet.so $CMSSW_BASE/external/$SCRAM_ARCH/lib/libmxnet.so

# compile
cd NNKit
scram b -j 8
```


The following installation instructions assume the user wants to process Run2016 data or Spring16 MC.

```
cd $CMSSW_BASE/src/
git clone -b TestMiniAOD git@github.com:susy2015/recipeAUX.git
git clone git@github.com:cms-jet/JetToolbox.git JMEAnalysis/JetToolbox -b jetToolbox_91X_v1 (https://github.com/cms-jet/JetToolbox/tree/jetToolbox_91X)
git clone -b CMSSW944 git@github.com:susy2015/SusyAnaTools.git
scram b -j 8
```

To produce ntuples with crab submission (google doc for production signup is https://docs.google.com/spreadsheets/d/17Hpp5S-UkiKvuugKxqbW0-3aLhiJrJP8MEEyHce_Lzw/edit#gid=0):
```
cd SusyAnaTools/SkimsAUX/workdir/prod/80X_crab_example
# Edit the line in MultiCrab3.py
# selSubmitKey = 'TEST ALL'
# to the sample keys you'd like to submit. Note we use space to seperate the sample keys.
# selSubmitKey = 'TTJets HTMHT'
# Will let you submit all the samples matching "*TTJets*" and "*HTMHT*"
# ----
# After submission, one can change the selSubmitKey to the following to monitor and re-submit failed jobs for you automatically
# selSubmitKey = 'TEST STATUS TTJets HTMHT'
```

To test the ntuple production interactively:
```
cd SusyAnaTools/SkimsAUX/workdir/prod/80X_crab_example
# do "cmsRun treeMaker_stopRA2.py" but with commandline options extracted from the MultiCrab3.py.
# For instance, for 2016 MC, do the following from
# https://github.com/susy2015/SusyAnaTools/blob/master/SkimsAUX/workdir/prod/80X_crab_example/MultiCrab3.py#L271:
# cmsRun treeMaker_stopRA2.py mcInfo=1 GlobalTag=80X_mcRun2_asymptotic_2016_miniAODv2 specialFix=JEC jecDBname=Spring16_25nsV1_MC maxEvents=1000
```
