SET(ALGORITHM_PROFILE_UID_Namespace "de.dkfz.matchpoint.itk")
SET(ALGORITHM_PROFILE_UID_Name "Demons.FastSymmetricForces.3D.multiRes.default")
SET(ALGORITHM_PROFILE_UID_Version "1.0.0")

SET(ALGORITHM_PROFILE_Description "Deformable 3D registration algorithm based on the concept of Thiron's demons using fast symmetric forces and using a 4 level multi resolution approach to get faster and more robust results. This algorithm is only suitable for mono modal tasks.")
SET(ALGORITHM_PROFILE_Contact "Ralf Floca\; sbr@dkfz-heidelberg.de")
SET(ALGORITHM_PROFILE_Citation "Tom Vercauteren, Xavier Pennec, Aymeric Perchant, and Nicholas Ayache. Diffeomorphic Demons Using ITK's Finite Difference Solver Hierarchy. Insight Journal , ISC/NA-MIC Workshop on Open Science at MICCAI 2007, October 2007.")

SET(ALGORITHM_PROFILE_DataType "Image")
SET(ALGORITHM_PROFILE_ResolutionStyle "4 (multi res)")
SET(ALGORITHM_PROFILE_DimMoving "3")
SET(ALGORITHM_PROFILE_ModalityMoving "any/monomodal")
SET(ALGORITHM_PROFILE_DimTarget "3")
SET(ALGORITHM_PROFILE_ModalityTarget "any/monomodal")
SET(ALGORITHM_PROFILE_Subject "any")
SET(ALGORITHM_PROFILE_Object "any")
SET(ALGORITHM_PROFILE_TransformModel "deformable")
SET(ALGORITHM_PROFILE_TransformDomain "lokal")
SET(ALGORITHM_PROFILE_Metric "Mean square difference")
SET(ALGORITHM_PROFILE_Keywords "deformable" "demons" "monomodal" "multi resolution")
